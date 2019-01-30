
project(cpp_utils)
include_directories(${PROJECT_SOURCE_DIR})

add_library(${PROJECT_NAME}
  Log.hpp
  Time.hpp
  Time.cpp
  File.hpp
  File.cpp
  Array.hpp
  System.hpp
  System.cpp
  String.hpp
  Bitwise.hpp
  LogData.hpp
  Singleton.hpp
  Dictionary.hpp
  ExceptionCatch.hpp
  ConditionalEvent.hpp
)
