#include <iostream>
#include "../include/http/downloadmpd.hpp"
//#include "../include/parsing/parsempd.hpp"
#include "string"

int main(){
  std::string url, filename, httperror;

  std::cin >> url;
  std::cout << "url good" << std::endl;
  std::cin >> filename;
  std::cout << std::endl;
  mpd testMpd;
  testMpd.downloadmpd(url.c_str(), filename.c_str(), httperror);
  if(httperror.size() > 0){
    std::cout << httperror;
  }


  
  return 0;
}