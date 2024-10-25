#pragma once
#include <functional>
#include <string>
#include <vector>

#include "iubuntu_fetch.h"

using std::string;
using std::vector;

class ubuntuFetch : public iubuntuFetch {
 private:
  string fetchUbuntuCloudImage() const;
  void parseUbuntuCloudImageJSON(
      std::function<void(const string&, vector<string>&)> parse_lambda,
      vector<string>& strings);

 public:
  ubuntuFetch() = default;
  vector<string> getSupportedReleases() override;
  string getCurrentLTSVersion() override;
  string getSHA256(string release) override;
  ~ubuntuFetch() = default;
};
