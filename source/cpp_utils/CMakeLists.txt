cmake_minimum_required(VERSION 3.9.2 FATAL_ERROR)

setup_lib(cpp_utils)

find_library(CORE_BLUETOOTH CoreBluetooth)

target_link_libraries(${PROJECT_NAME} ${CORE_BLUETOOTH})

