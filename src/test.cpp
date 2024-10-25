#include <curl/curl.h>

#include <catch2/catch_test_macros.hpp>
#include <map>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "libcurl_util.h"
#include "ubuntu_fetch.h"

using std::map;
using std::string;
using json = nlohmann::json;

string fetchUbuntuCloudImageJSONString() {
  CURL* curl;
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

TEST_CASE("ubuntuFetch") {
  json ubuntu_cloud_image_json = json::parse(fetchUbuntuCloudImageJSONString());

  SECTION("Get Supported Releases") {
    ubuntuFetch u{};
    vector<string> supported_releases{};

    // parse out supported releases

    // for each product (ubuntu release)
    for (const auto& [key, value] :
         ubuntu_cloud_image_json["products"].items()) {
      // if it is supported and contains the substring "amd64"
      if (value["supported"] == true && key.find("amd64") != std::string::npos)
        supported_releases.push_back(value["release_title"]);
    }

    CHECK(u.getSupportedReleases() == supported_releases);
  }

  SECTION("Get Current LTS Version") {
    ubuntuFetch u{};
    string current_lts_version{};

    // parse out current lts version
    // for each product (ubuntu release), looping through keys (exploits the
    // fact that keys are stored in alphanumeric order to minimize search time)
    for (const auto& [key, value] :
         ubuntu_cloud_image_json["products"].items()) {
      if (key.find("amd64") != std::string::npos &&
          value["release_title"].get<string>().find("LTS") != std::string::npos)
        current_lts_version = value["release_title"];
    }

    CHECK(u.getCurrentLTSVersion() == current_lts_version);
  }

  SECTION("Get SHA 256 for each Ubuntu Release") {
    ubuntuFetch u{};
    string mock_release_number{"24.04"};
    string sha256{};

    // parse out sha256 and compare
    for (const auto& [key, value] :
         ubuntu_cloud_image_json["products"].items()) {
      if (key.find("amd64") != std::string::npos &&
          value["version"] == mock_release_number) {
        // exploits the fact that keys are stored in alphanumeric order,
        // leaving the largest number (and thus, most recent version) at the
        // end
        auto current_version = value["versions"].back();
        sha256 = current_version["items"]["disk1.img"]["sha256"].get<string>();
      }
    }

    CHECK(u.getSHA256(mock_release_number) == sha256);
  }
}
