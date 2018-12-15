
project(cpp_utils)
include_directories(${PROJECT_SOURCE_DIR})

add_library(${PROJECT_NAME}
  Log.hpp
  Time.hpp
  Time.cpp
  File.hpp
  File.cpp
  Array.hpp
  Event.hpp
  System.hpp
  System.cpp
  String.hpp
  String.cpp
  Bitwise.hpp
  Lifehack.hpp
  Dictionary.hpp
  Singleton.hpp
  ExceptionCatch.hpp
  ConditionalEvent.hpp
)
