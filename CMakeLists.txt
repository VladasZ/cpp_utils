cmake_minimum_required(VERSION 3.9.2 FATAL_ERROR)

include(${CMAKE_BINARY_DIR}/build_info.cmake)
include(${BUILD_SCRIPT_PATH})

set(CMAKE_CXX_STANDARD 17)

project(cpp_utils)

if(${DESKTOP_BUILD})
	add_definitions(-DUI_DESKTOP=1)
	add_definitions(-DIOS=0)
endif()

if(${IOS})
	add_definitions(-DUI_DESKTOP=0)
	add_definitions(-DIOS=1)
endif()

add_subdirectory(source/cpp_utils)

if(${DESKTOP_BUILD})
	add_subdirectory(source/cpp_utils_test)
endif()
