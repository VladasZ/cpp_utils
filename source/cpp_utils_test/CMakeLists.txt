cmake_minimum_required(VERSION 3.9.2 FATAL_ERROR)

setup_exe(cpp_utils_test)
link_project(cpp_utils)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "tests")
