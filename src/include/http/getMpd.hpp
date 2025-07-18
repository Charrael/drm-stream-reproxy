#include "curl/curl.h"
#include <string>
#include <stdio.h>
#include <filesystem>

static size_t writeFunction(char *received, size_t size, size_t nmemb, void *stream){
  FILE* fp = static_cast<FILE *>(stream);

  size_t written = fwrite(received, size, nmemb, fp);

  return written;
}
void getMpd(std::string &url, const std::string &channelPath){
  
  FILE *mpd = fopen(channelPath.c_str(), "wb");
  if(!mpd){
    throw std::runtime_error("couldn't write location: " + channelPath);
  }

  CURL *handle;
  CURLcode res;
  
  curl_global_init(CURL_GLOBAL_DEFAULT);
  handle = curl_easy_init();
  
  curl_easy_setopt(handle, CURLOPT_URL, url.c_str());
  curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, writeFunction);
  curl_easy_setopt(handle, CURLOPT_WRITEDATA, mpd);

  res = curl_easy_perform(handle);

  if(res != CURLE_OK){
    fclose(mpd);
    std::string errorstring = curl_easy_strerror(res);
    throw std::runtime_error("couldnt perform network request: " + errorstring);
  }

  curl_easy_cleanup(handle);
  curl_global_cleanup();

  fclose(mpd);
}