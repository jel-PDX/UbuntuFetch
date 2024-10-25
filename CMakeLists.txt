cmake_minimum_required(VERSION 3.30.4)

project(UbuntuFetch VERSION 1.0
                    DESCRIPTION "A CLI that fetches Ubuntu cloud image data"
                    LANGUAGES CXX)



# Pull in libcurl
find_package(CURL REQUIRED)

# Create main executable
add_executable(ubuntufetch src/main.cpp)
target_link_libraries(ubuntufetch ${CURL_LIBRARIES})

# Pull in Catch2
find_package(Catch2 3 REQUIRED)
add_executable(tests src/test.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
