#include "ubuntu_fetch.h"

#include <curl/curl.h>

#include <nlohmann/json.hpp>

#include "libcurl_util.h"

using json = nlohmann::json;

string ubuntuFetch::fetchUbuntuCloudImage() const {
  CURL *curl;
  CURLcode res;
  std::string read_cloud_img{};
  curl_global_init(CURL_GLOBAL_ALL);

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

void ubuntuFetch::parseUbuntuCloudImageJSON(
    std::function<void(const string &, vector<string> &)> parse_lambda,
    vector<string> &strings) {
  string image_JSON{fetchUbuntuCloudImage()};

  parse_lambda(image_JSON, strings);
}

vector<string> ubuntuFetch::getSupportedReleases() {
  vector<string> supported_releases{};

  // parse out supported releases

  auto parse_lambda = [](const string &image_JSON, vector<string> &strings) {
    json map = json::parse(image_JSON);
    // for each product (ubuntu release)
    for (const auto &[key, value] : map["products"].items()) {
      // if it is supported and contains the substring "amd64"
      if (value["supported"] == true &&
          key.find("amd64") != std::string::npos) {
        strings.push_back(value["release_title"]);
      }
    }
  };

  parseUbuntuCloudImageJSON(parse_lambda, supported_releases);

  return supported_releases;
}

string ubuntuFetch::getCurrentLTSVersion() {
  vector<string> current_lts_version{};

  // parse out current lts version
  // for each product (ubuntu release), looping through keys (exploits the
  // fact that keys are stored in alphanumeric order to minimize search time)
  auto parse_lambda = [](const string &image_JSON, vector<string> &strings) {
    json ubuntu_cloud_image_json = json::parse(image_JSON);
    for (const auto &[key, value] :
         ubuntu_cloud_image_json["products"].items()) {
      if (key.find("amd64") != std::string::npos &&
          value["release_title"].get<string>().find("LTS") != std::string::npos)
        strings.push_back(value["release_title"]);
    }
  };

  parseUbuntuCloudImageJSON(parse_lambda, current_lts_version);

  return current_lts_version.back();
}

string ubuntuFetch::getSHA256(string release_number) {
  vector<string> sha256{};

  // parse out sha256
  auto parse_lambda = [release_number](const string &image_JSON,
                                       vector<string> &strings) {
    json ubuntu_cloud_image_json = json::parse(image_JSON);
    for (const auto &[key, value] :
         ubuntu_cloud_image_json["products"].items()) {
      if (key.find("amd64") != std::string::npos &&
          value["version"] == release_number) {
        // exploits the fact that keys are stored in alphanumeric order,
        // leaving the largest number (and thus, most recent version) at the
        // end
        auto current_version = value["versions"].back();
        strings.push_back(
            current_version["items"]["disk1.img"]["sha256"].get<string>());
      }
    }
  };

  parseUbuntuCloudImageJSON(parse_lambda, sha256);

  return sha256.back();
}
