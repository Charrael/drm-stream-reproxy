#include <fstream>
#include <iostream>
#include <mutex>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

struct SelectedVariants
{
  std::string video;
  std::vector<std::string> audio;
};
struct streamData
{
  std::string url;
  bool active = true;

  // metadata
  std::string channelName;
  std::string group;
  std::string tvgID, tvgLogo;

  // DRM
  std::string videoDecryptionKey{};
  std::string audioDecryptionKey{};

  // Variant lists
  std::vector<std::string> videoQualities;
  std::vector<std::string> audioTracks;

  // User‑selected variant
  SelectedVariants selectedVariants;
};

struct channelConfig
{
  int channelCount;
  int lastId;
  std::unordered_map<int, streamData> streams;
};

std::mutex jsonMutex;

void loadJsonData(std::string *databaseLocation, channelConfig *cfg)
{
  std::lock_guard<std::mutex> lock(jsonMutex);
  std::ifstream database(*databaseLocation);
  if (!database.is_open())
    throw std::runtime_error("Cannot open database file: " + *databaseLocation);
  json j_database = json::parse(database);

  cfg->channelCount = j_database.value("channelCount", 0);
  cfg->lastId = j_database.value("lastid", 0);

  int countedChannels{};

  if (!j_database.contains("channels") || !j_database["channels"].is_object())
  {
    std::cout << "WARNING: 'channels' key missing or malformed in JSON\n";
    return;
  }

  for (auto &item : j_database["channels"].items())
  {
    auto &key = item.key();
    auto &value = item.value();

    int id = std::stoi(key);

    streamData data;
    SelectedVariants variants;

    data.url = value.value("url", "");
    data.active = value.value("active", false);
    data.channelName = value.value("channelName", "");
    data.group = value.value("group", "");
    data.tvgID = value.value("tvg-ID", "");
    data.tvgLogo = value.value("tvg-logo", "");
    data.videoDecryptionKey = value.value("videoDecryptionKey", "");
    data.audioDecryptionKey = value.value("audioDecryptionKey", "");
    data.videoQualities = value.value("videoQualities", std::vector<std::string>{});
    data.audioTracks = value.value("audioTracks", std::vector<std::string>{});

    auto &variantsJson = value["selectedVariants"];
    variants.video = variantsJson.value("video", "");
    variants.audio = variantsJson.value("audio", std::vector<std::string>{});
    data.selectedVariants = variants;

    cfg->streams.insert({id, data});
    countedChannels++;
  }

  if (countedChannels != cfg->channelCount)
  {
    std::cout << "WARNING: expected " << cfg->channelCount << " found " << countedChannels << " channels\n";
  }
}

void to_json(json &j, const SelectedVariants &v)
{
  j = json{
      {"video", v.video},
      {"audio", v.audio}};
}

void to_json(json &j, const streamData &d)
{
  j = json{
      {"url", d.url},
      {"active", d.active},
      {"channelName", d.channelName},
      {"group", d.group},
      {"tvg-ID", d.tvgID},
      {"tvg-logo", d.tvgLogo},
      {"videoDecryptionKey", d.videoDecryptionKey},
      {"audioDecryptionKey", d.audioDecryptionKey},
      {"videoQualities", d.videoQualities},
      {"audioTracks", d.audioTracks},
      {"selectedVariants", d.selectedVariants}};
}

void writeJsonData(std::string *databaseLocation, channelConfig *cfg)
{
  std::lock_guard<std::mutex> lock(jsonMutex);
  std::ofstream database(*databaseLocation, std::ios::out | std::ios::trunc);
  if (!database.is_open())
    throw std::runtime_error("Cannot open database file: " + *databaseLocation);

  json j_database = {
      {"channelCount", cfg->channelCount},
      {"lastid", cfg->lastId},
      {"channels", json::object()}};

  for (auto &pair : cfg->streams)
  {
    int id = pair.first;
    const streamData &data = pair.second;

    j_database["channels"][std::to_string(id)] = data;
  }

  database << j_database.dump(2);
}