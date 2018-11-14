
project(cpp_utils)
include_directories(${PROJECT_SOURCE_DIR})

add_library(${PROJECT_NAME}
  File.cpp
  Time.cpp
  String.cpp
  System.cpp
)
