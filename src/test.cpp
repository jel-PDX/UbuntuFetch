#include <curl/curl.h>

#include <catch2/catch_test_macros.hpp>

using std::string;

string fetchUbuntuCloudImageJSONString() {
  CURL *curl;
  CURLcode res;
  curl_global_init(CURL_GLOBAL_ALL);
  string read_cloud_image{};

  curl = curl_easy_init();

  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL,
                     "https://cloud-images.ubuntu.com/releases/streams/v1/"
                     "com.ubuntu.cloud:released:download.json");

    res = curl_easy_perform(curl);

    curl_easy_cleanup(curl);
  }

  return read_cloud_image;
}

TEST_CASE("stub") { REQUIRE(true); }
