cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(cpp_utils)

add_catalog_recursive(${PROJECT_SOURCE_DIR} /source SOURCE)
add_library(${PROJECT_NAME} ${SOURCE})
