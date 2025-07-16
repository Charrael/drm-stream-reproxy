#include <iostream>
#include "../data/DataHandling.hpp"

channelConfig cfg;
//startup/stop all streams
void startStreams(std::string *databaseLocation){
  try
  {
    loadJsonData(databaseLocation, &cfg);
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    std::exit(1);
  }
  
  
}

void addNewStream(){
  
}