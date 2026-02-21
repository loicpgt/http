cmake_minimum_required(VERSION 3.10)
project(http_core C)

file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/**.c)
add_library(http_core SHARED ${SOURCE_FILES})

target_include_directories(http_core PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)