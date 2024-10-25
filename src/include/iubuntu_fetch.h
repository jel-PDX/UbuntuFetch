#pragma once
#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

class iubuntuFetch {
 public:
  virtual vector<string> getSupportedReleases() = 0;
  virtual string getCurrentLTSVersion() = 0;
  virtual string getSHA256(string release) = 0;
  virtual ~iubuntuFetch() = default;
};
