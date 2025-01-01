#include <iostream>
#include "../include/http/downloadmpd.hpp"
#include "string"

int main(){
  std::string url, filename, httperror;

  std::cin >> url;
  std::cout << "url good" << std::endl;
  std::cin >> filename;
  std::cout << std::endl;
  downloadmpd(url.c_str(), filename.c_str(), httperror.c_str());
  
  if(httperror.size() > 0){
    std::cout << httperror;
  }
  
  return 0;
}