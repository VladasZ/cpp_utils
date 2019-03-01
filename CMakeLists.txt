cmake_minimum_required(VERSION 3.9.2 FATAL_ERROR)

include(${CMAKE_BINARY_DIR}/build_info.cmake)
include(${BUILD_SCRIPT_PATH})

set(CMAKE_CXX_STANDARD 17)

project(cpp_utils)

add_subdirectory(source/cpp_utils)
add_subdirectory(source/cpp_utils_test)
