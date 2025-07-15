#include <iostream>
#include <thread>
#include "include/streams/MediaManager.hpp"

const std::string version = "0.0";

int main(int argc, char *argv[])
{
  std::string arg1 = argc > 1 ? std::string(argv[1]) : "";
  if (argc == 1)
  {
    std::cout << "Running drm-stream-reproxy alpha build\n";
    std::cout << "use --help for more information\n";
    return 0;
  }
  else if (arg1 == "--help")
  {
    std::cout << R"(
    Usage : drm-sr [options]
    OPTIONS
    
    --help       Show this help message
    --version    Print version info
    start        Run the program)"
              << std::endl;
    return 0;
  }
  else if (arg1 == "--version")
  {
    std::cout << "drm-sr version " << version << std::endl;
  }
  else if (arg1 == "start")
  {
    std::string streamsLocation = "list.json"; 
    bool streamsActive = true;
    std::thread t1(runningStreams, &streamsActive, &streamsLocation);
    t1.detach();
    bool isRunning{true};
    do
    {
      std::string option;
      std::cout << R"(
      Choose what you would like to do
        add "dash url" "key"          add new stream
        remove "index"                remove stream by index
        list                          get list of all stream and their indexes
        stop                          stop the running program

      )";
      std::cin >> option;

      if (option.substr(0, 3) == "add")
      {
      }
      else if (option.substr(0, 6) == "remove")
      {
      }
      else if (option == "list")
      {
      }
      else if (option == "stop")
      {
        return 0;
      }

    } while (isRunning);
  }
}