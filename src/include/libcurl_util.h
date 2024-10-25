#pragma once
#include <cstddef>
#include <string>

using std::string;

namespace libcurlUtil {
size_t cb(void *contents, size_t size, size_t nmemb, void *userp);
}
