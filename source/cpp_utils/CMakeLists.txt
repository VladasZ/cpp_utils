cmake_minimum_required(VERSION 3.9.2 FATAL_ERROR)

setup_lib(cpp_utils)

if(APPLE)
    find_library(APP_KIT AppKit)
    find_library(FOUNDATION Foundation )
    find_library(CORE_BLUETOOTH CoreBluetooth)

    target_link_libraries(${PROJECT_NAME} ${APP_KIT})
    target_link_libraries(${PROJECT_NAME} ${FOUNDATION})
    target_link_libraries(${PROJECT_NAME} ${CORE_BLUETOOTH})
endif()
