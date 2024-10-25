#pragma once
#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

class iubuntuFetch {
 public:
  virtual vector<string> getSupportedReleases() const = 0;
  virtual string getCurrentLTSVersion() const = 0;
  virtual string getSHA256(string release) const = 0;
  virtual ~iubuntuFetch() = default;
};
