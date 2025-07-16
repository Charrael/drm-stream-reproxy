#include <fstream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

struct SelectedVariants{
  std::string video;
  std::vector<std::string> audio;
};
struct streamData
{
  std::string url;
  bool active = true;

  //metadata
  std::string channelName;
  std::string group;
  std::string tvgID, tvgLogo;

  //DRM
  std::string videoDecryptionKey{};
  std::string audioDecryptionKey{};

  // Variant lists
  std::vector<std::string> videoQualities;
  std::vector<std::string> audioTracks;

  // User‑selected variant
  SelectedVariants selectedVariants;
};

struct channelConfig{
  std::unordered_map<std::string, streamData> streams;
};
void loadJsonData(std::string *databaseLocation){
  std::ifstream database(*databaseLocation);
  json j_database = json::parse(database);

  

}