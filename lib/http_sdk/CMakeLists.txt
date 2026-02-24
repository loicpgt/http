cmake_minimum_required(VERSION 3.10)
project(http_sdk CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/**.cpp)
add_library(http_sdk SHARED ${SOURCE_FILES})

target_include_directories(http_sdk PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(../http_core ${CMAKE_BINARY_DIR}/http_core_build)
target_link_libraries(http_sdk PRIVATE http_core)