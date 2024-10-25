#include <curl/curl.h>

#include <catch2/catch_test_macros.hpp>
#include <map>
#include <string>
#include <vector>

#include "libcurl_util.h"
#include "ubuntu_fetch.h"

using std::map;
using std::string;

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
  string ubuntu_cloud_image_json_string{fetchUbuntuCloudImageJSONString()};

  SECTION("Get Supported Releases") {
    ubuntuFetch u{};
    vector<string> supported_releases{};

    // do json parsing

    CHECK(u.getSupportedReleases() == supported_releases);
  }

  SECTION("Get Current LTS Version") {
    ubuntuFetch u{};
    string current_lts_version{};

    // do json parsing

    CHECK(u.getCurrentLTSVersion() == current_lts_version);
  }

  SECTION("Get SHA 256 for each Ubuntu Release") {
    map<string, string> ubuntu_releases_sha256_map{};
    ubuntuFetch u{};
    string sha256{};

    // do json parsing (pairing heach ubuntu
    // release in the cloud image with its sha256 checksum is part of this)

    for (const auto& [release, sha256] : ubuntu_releases_sha256_map)
      CHECK(u.getSHA256(release) == ubuntu_releases_sha256_map[release]);
  }
}
