cmake_minimum_required(VERSION 3.10)
project(http)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)

add_executable(http main.cpp)

add_subdirectory(lib/http_sdk ${CMAKE_BINARY_DIR}/http_sdk_build)
target_link_libraries(http PRIVATE http_sdk)
