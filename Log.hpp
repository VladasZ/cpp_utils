//
//  Log.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 7/28/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#pragma once

#include <string.h>
#include <iostream>

#include "String.hpp"

#ifdef DEBUG

#define LOG_LOCATION_ENABLED true
#define LOG_ERRORS true

#define __FILENAME__ String::file_name((strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__))

#define LOCATION_INFO __FILENAME__, __func__, __LINE__
#define LOCATION_PARAMETERS std::string fileName, const char* function, int line

#if LOG_LOCATION_ENABLED
#define LOCATION(file, func, line) << "[" << file << "::" << func << " - " << line << "] "
#else
#define LOCATION(file, func, line) << " "
#endif

#define __log(message, type, file, func, line)\
std::cout << "[" << type << "]" \
LOCATION(file, func, line)\
<< message << std::endl;

#define __logI(message, file, func, line) __log(message, "INFO",    file, func, line)
#define __logW(message, file, func, line) __log(message, "WARNING", file, func, line)

#if LOG_ERRORS
#define __logE(message, file, func, line) __log(message, "ERROR",   file, func, line)
#else
#define __logE(message, file, func, line)
#endif

#define Log(message)     __logI(message, __FILENAME__, __func__, __LINE__)
#define Warning(message) __logW(message, __FILENAME__, __func__, __LINE__)
#define Error(message)   __logE(message, __FILENAME__, __func__, __LINE__)
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
