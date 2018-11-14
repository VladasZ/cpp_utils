
project(cpp_utils)
include_directories(${PROJECT_SOURCE_DIR})

add_library(${PROJECT_NAME}
  Log.hpp
  String.cpp
  File.cpp
)
