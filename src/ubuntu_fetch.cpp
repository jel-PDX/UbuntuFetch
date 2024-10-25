#include "ubuntu_fetch.h"

vector<string> ubuntuFetch::getSupportedReleases() const {
  vector<string> v{};
  return v;
}

string ubuntuFetch::getCurrentLTSVersion() const { return ""; }

string ubuntuFetch::getSHA256(string release) const { return ""; }
