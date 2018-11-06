cmake_minimum_required(VERSION 3.11)

project(json)

set(json_BIN_DIR ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${json_BIN_DIR})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeScripts")

include(make_check_macros)

setup_make_check()

add_definitions(-std=c++1y)

add_subdirectory(src)

add_subdirectory(tests EXCLUDE_FROM_ALL)
