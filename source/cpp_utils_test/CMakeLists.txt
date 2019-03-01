cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(cpp_utils_test)

add_catalog_recursive(${PROJECT_SOURCE_DIR} /source SOURCE)
add_executable(${PROJECT_NAME} ${SOURCE})

link_project(cpp_utils)
