cmake_minimum_required(VERSION 2.8)
project(cmordor)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
add_definitions( "-Wall -g -O0 ")
include_directories("/usr/include/postgresql")

add_subdirectory("${CMAKE_SOURCE_DIR}/test/")
message( status, "message")
add_subdirectory("${CMAKE_SOURCE_DIR}/cmordor/")
