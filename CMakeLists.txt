cmake_minimum_required(VERSION 3.30.4)

project(UbuntuFetch VERSION 1.0
                    DESCRIPTION "A CLI that fetches Ubuntu cloud image data"
                    LANGUAGES CXX)

# Create main executable
add_executable(ubuntufetch src/main.cpp)
