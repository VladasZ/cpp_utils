cmake_minimum_required(VERSION 3.9.2 FATAL_ERROR)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
	include(build/build_tools_generated.cmake)
	include(${CMAKE_UTILS_PATH})
endif()

set(CMAKE_CXX_STANDARD 17)

project(cpp_utils)

add_subdirectory(source/cpp_utils)

if(${DESKTOP_BUILD})
	add_subdirectory(source/cpp_utils_test)
endif()
