#include "libcurl_util.h"

namespace libcurlUtil {
size_t cb(void *contents, size_t size, size_t nmemb, void *userp) {
  ((std::string *)userp)->append((char *)contents, size * nmemb);

  return size * nmemb;
}
};  // namespace libcurlUtil
