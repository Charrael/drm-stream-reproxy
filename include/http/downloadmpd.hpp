#include "curl/curl.h"
#include <stdio.h>
#include <string>

class mpd{
  private:
  public:
    const char *mpdfilename;
    int downloadmpd(const char *url, const char *filename, std::string httperror);
    bool deletempd();
};

size_t write_data(void *buffer, size_t size, size_t nmemb, void *file){
  size_t written = fwrite(buffer, size, nmemb, (FILE *)file);
  return written;
}

int mpd::downloadmpd(const char *url, const char *filename, std::string httperror){
  mpdfilename = filename;
  CURL *curl = curl_easy_init();
  FILE *file;
  CURLcode res;

  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);

    file = fopen(mpdfilename, "wb");
    if(file){
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
      res = curl_easy_perform(curl);
      fclose(file);
    }
    httperror = curl_easy_strerror(res);
    curl_easy_cleanup(curl);
  }
  
  return (res==CURLE_OK) ? 0 : 1;
  
}

bool mpd::deletempd(){
  return remove(mpdfilename) == 0;
}