cmake_minimum_required(VERSION 3.9.2 FATAL_ERROR)

include(${CMAKE_BINARY_DIR}/build_info.cmake)
include(${BUILD_SCRIPT_PATH})

set(CMAKE_CXX_STANDARD 17)

project(cpp_utils)

add_subdirectory(source/cpp_utils)
add_subdirectory(source/cpp_utils_test)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
  foreach(var ${GIT_DEPENDENCIES})
	add_subdirectory(${var} "${var}/dep_build")
  endforeach()
endif()
