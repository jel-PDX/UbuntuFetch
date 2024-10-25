#include <curl/curl.h>

#include <catch2/catch_test_macros.hpp>

#include "libcurl_util.h"

using std::string;

string fetchUbuntuCloudImageJSONString() {
  CURL *curl;
  CURLcode res;
  curl_global_init(CURL_GLOBAL_ALL);
  string read_cloud_img{};

  curl = curl_easy_init();

  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL,
                     "https://cloud-images.ubuntu.com/releases/streams/v1/"
                     "com.ubuntu.cloud:released:download.json");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, libcurlUtil::cb);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_cloud_img);

    res = curl_easy_perform(curl);

    curl_easy_cleanup(curl);
  }

  return read_cloud_img;
}

TEST_CASE("stub") { REQUIRE(true); }
