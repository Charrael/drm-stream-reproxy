#include <iostream>
#include <filesystem>
#include "../data/DataHandling.hpp"
#include "../http/getMpd.hpp"


class playlist{
  private:
    channelConfig cfg;
    std::string databaseDir;
    std::string databaseLocation;
  public:
    void addNewStream(std::string &url);
    void removeStream();
    void listStreams();
    void toggleStream();
    void shutDown();
    void setDatabaseLocation(const std::string &dirPath);
    void startStreams();
    //void editStream();
};

void playlist::setDatabaseLocation(const std::string &dirPath){
  databaseDir = std::filesystem::absolute(dirPath).string();
  databaseLocation = databaseDir + "/database.json";

  if(std::filesystem::exists(databaseLocation)){
    throw(std::runtime_error("Error: database already exists at given Location"));
  }
  std::filesystem::create_directories(databaseDir);
  std::ofstream database(databaseLocation, std::ios::out | std::ios::trunc);
  if(!database)
    throw(std::runtime_error("couldnt write database at:" + databaseDir));

  json j_database = {
    {"channelCount", 0},
    {"channels", json::object({})}
  };
  database << j_database.dump(2);
}

//startup/stop all streams
void playlist::startStreams(){
  try
  {
    loadJsonData(&databaseLocation, &cfg);
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    std::exit(1);
  }
}

void playlist::addNewStream(std::string &url){
  const std::string channelPath = databaseDir + "/" + std::to_string(cfg.lastId + 1);
  if (std::filesystem::exists(channelPath))
    throw(std::runtime_error("Error: Database mismatch last ID isnt last"));

  std::filesystem::create_directories(channelPath);

  getMpd(url, channelPath);
  //parseMpd()

  cfg.lastId += 1;
}