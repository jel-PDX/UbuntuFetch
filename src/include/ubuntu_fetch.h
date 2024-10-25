#pragma once
#include <string>
#include <vector>

#include "iubuntu_fetch.h"

using std::string;
using std::vector;

class ubuntuFetch : public iubuntuFetch {
 public:
  ubuntuFetch() = default;
  vector<string> getSupportedReleases() const override;
  string getCurrentLTSVersion() const override;
  string getSHA256(string release) const override;
  ~ubuntuFetch() = default;
};
