cmake_minimum_required(VERSION 3.9.2 FATAL_ERROR)

setup_lib(cpp_utils)

if(APPLE)

    if(MAC_BUILD)
        find_library(UI_LIB AppKit)
    else()
        find_library(UI_LIB UIKit)
    endif()

    find_library(FOUNDATION Foundation)
    find_library(CORE_BLUETOOTH CoreBluetooth)

    target_link_libraries(${PROJECT_NAME} ${UI_LIB})
    target_link_libraries(${PROJECT_NAME} ${FOUNDATION})
    target_link_libraries(${PROJECT_NAME} ${CORE_BLUETOOTH})

endif()
