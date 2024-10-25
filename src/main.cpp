#include <cstring>
#include <iostream>

#include "ubuntu_fetch.h"

using std::cout;
using std::endl;
using std::string;

int main(int argc, char* argv[]) {
  if (argc < 2) {
    cout << "error: invalid args\n\nrun ubuntufetch --help or ubuntufetch -h "
            "for help\n";
    return 1;
  }

  string arg1{argv[1]};

  if (arg1 == "--help" || arg1 == "-h") {
    cout << "flags:\n--supported-releases or -r: fetch supported releases"
         << "\n--current-lts or -c: fetch current lts release of ubuntu"
         << "\n--sha256 <release_number> or -s <release_number>: fetch sha256 "
            "checksum of given release (ex. 24.04)"
         << "\n\nex:\nubuntufetch --sha256 17.04" << std::endl;
    return 0;
  }

  ubuntuFetch u{};

  if (arg1 == "--supported-releases" || arg1 == "-r")
    for (auto data : u.getSupportedReleases()) cout << data << endl;
  else if (arg1 == "--current-lts" || arg1 == "-c")
    cout << u.getCurrentLTSVersion() << endl;
  else if (arg1 == "--sha256" || arg1 == "-s") {
    if (argc < 3) {
      cout << "error: invalid args\n\nrun ubuntufetch --help or ubuntufetch -h "
              "for help\n";
      return 1;
    }
    cout << u.getSHA256((string)argv[2]) << endl;
  } else
    cout << "ERROR: undefined args\n";

  return 0;
};
