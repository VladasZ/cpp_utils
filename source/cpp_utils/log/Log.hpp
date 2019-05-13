//
//  Log.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 7/28/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#pragma once

#ifdef __arm__
#include "mbed.h"

static Serial *serial_transmitter =
  []{
    auto serial = new Serial(USBTX, USBRX);
    serial->baud(230400);
    return serial;
  }();
#endif

#include <string.h>
#include <iostream>

#include "../stl/StringUtils.hpp"

#define LOG_ENABLED

#ifdef LOG_ENABLED

#define LOG_LOCATION_ENABLED true
#define LOG_ERRORS true

#define UTILS_INTERNAL_FILENAME cu::string::file_name((strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__))

#define LOCATION_INFO UTILS_INTERNAL_FILENAME, __func__, __LINE__
#define LOCATION_PARAMETERS const std::string& fileName, const char* function, int line

#if LOG_LOCATION_ENABLED
#define LOCATION(file, func, line) << "[" << file << "::" << func << " - " << line << "] "
#else
#define LOCATION(file, func, line) << " "
#endif

#define UTILS_INTERNAL_LOG(message, type, file, func, line)\
  std::cout /*"[" << type << "]"*/					   \
LOCATION(file, func, line)\
<< message << std::endl;

#define UTILS_INTERNAL_LOG_INFO(message, file, func, line)    UTILS_INTERNAL_LOG(message, "INFO",    file, func, line)
#define UTILS_INTERNAL_LOG_WARNING(message, file, func, line) UTILS_INTERNAL_LOG(message, "WARNING", file, func, line)

#if LOG_ERRORS
#define UTILS_INTERNAL_LOG_ERROR(message, file, func, line)   UTILS_INTERNAL_LOG(message, "ERROR",   file, func, line)
#else
#define __logE(message, file, func, line)
#endif

#define Log(message)     UTILS_INTERNAL_LOG_INFO   (message, UTILS_INTERNAL_FILENAME, __func__, __LINE__)
#define Warning(message) UTILS_INTERNAL_LOG_WARNING(message, UTILS_INTERNAL_FILENAME, __func__, __LINE__)
#define Error(message)   UTILS_INTERNAL_LOG_ERROR  (message, UTILS_INTERNAL_FILENAME, __func__, __LINE__)
#define Endl std::cout << std::endl

#define PING Warning("")
#define UNEXPECTED Error("")

#else

#define Log(message)
#define Warning(message)
#define Error(message)
#define Endl
#define PING
#define UNEXPECTED

#endif

#define Info(message) Log((message))
#define Logvar(variable) Log(#variable << " : " << (variable))
#define NOT_IMPLEMENTED Error("Not implemented")
#define Fatal(message) { std::cout << message << std::endl; std::terminate(); }
