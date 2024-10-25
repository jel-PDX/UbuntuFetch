cmake_minimum_required(VERSION 3.30.4)

project(UbuntuFetch VERSION 1.0
                    DESCRIPTION "A CLI that fetches Ubuntu cloud image data"
                    LANGUAGES CXX)



# Pull in libcurl
find_package(CURL REQUIRED)

# Pull in nlohmann json
find_package(nlohmann_json 3.10.5 REQUIRED)

# Lib libcurl_util
add_library(libcurl_util src/libcurl_util.cpp)
target_include_directories(libcurl_util PUBLIC src/include ${CURL_INCLUDE_DIR})
target_link_libraries(libcurl_util PUBLIC ${CURL_LIBRARIES})

# Lib ubuntu_fetch
add_library(ubuntu_fetch src/ubuntu_fetch.cpp)
target_include_directories(ubuntu_fetch PUBLIC src/include)
target_link_libraries(ubuntu_fetch PUBLIC libcurl_util nlohmann_json::nlohmann_json)

# Pull in Catch2
find_package(Catch2 3 REQUIRED)
add_executable(tests src/test.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain ${CURL_LIBRARIES} libcurl_util ubuntu_fetch nlohmann_json::nlohmann_json)

# Create main executable
add_executable(ubuntufetch src/main.cpp)
target_link_libraries(ubuntufetch ubuntu_fetch)

