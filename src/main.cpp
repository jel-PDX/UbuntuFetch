#include <curl/curl.h>

#include <iostream>

int main() {
  CURL *curl;
  CURLcode res;
  curl_global_init(CURL_GLOBAL_ALL);

  curl = curl_easy_init();

  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL,
                     "https://cloud-images.ubuntu.com/releases/streams/v1/"
                     "com.ubuntu.cloud:released:download.json");

    res = curl_easy_perform(curl);

    curl_easy_cleanup(curl);
  }

  return 0;
}
