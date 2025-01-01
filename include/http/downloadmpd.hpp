#include "curl/curl.h"
#include <cstring>

int downloadmpd(const char *url, const char *filename, const char*httperror){
  CURL *curl;
  FILE *mpd;
  CURLcode res;

  curl = curl_easy_init();
  mpd = fopen(filename,"wb");

  curl_easy_setopt(curl, CURLOPT_URL, url);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
  curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, mpd);

  res = curl_easy_perform(curl);
  curl_easy_cleanup(curl);
  fclose(mpd);

  if(res == CURLE_OK){
    return 0;
  }else{
    httperror = curl_easy_strerror(res);
    return 1;
  }

  
}