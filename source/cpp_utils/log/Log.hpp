//
//  Log.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 12/8/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include <string>
#include <cstring>
#include <sstream>
#include <iostream>

#ifdef ARDUINO
#include <HardwareSerial.h>
#else
#include "MetaHelpers.hpp"
#endif

#define UTILS_LOG_ENABLED

namespace cu {

    class Log {

    public:

        static std::string last_path_component(const std::string& path) {
            return (strrchr(path.c_str(), '/') ? strrchr(path.c_str(), '/') + 1 : path.c_str());
        }

        static void internal_log(const std::string& message, const std::string& file, const std::string& func, int line) {
            std::string result_message = location(file, func, line) + " " + message;
#ifdef ARDUINO
            Serial.println(result_message.c_str());
#elif ANDROID_BUILD
            __android_log_print(ANDROID_LOG_DEBUG, "C++ Log", "%s", result_message.c_str());
#else
            std::cout << result_message << std::endl;
#endif
        }

        static std::string location(const std::string& file, const std::string& func, int line) {
            std::string clean_file = last_path_component(file);
            if (clean_file.back() == 'm') {
                return func + " - " + to_string(line) + "] ";
            }
            return "[" + clean_file + "::" + func + " - " + to_string(line) + "]";
        }

        template <class T>
        static void log(const T& message, const std::string& file, const std::string& func, int line) {
            internal_log(to_string(message), file, func, line);
        }

        template <class T>
        static std::string to_string(const T& value) {
//            if constexpr (cu::is_std_vector_v<T>) {
//                std::string result = "\n";
//                for (auto val : value) {
//                    result += Log::to_string(val) + "\n";
//                }
//                return result;
//            }
//#ifdef __OBJC__
//                else if constexpr (cu::is_objc_object_v<T>) {
//                if (value == nullptr) {
//                    return "nil";
//                }
//                return [[value description] cString];
//            }
//#endif
//            else if constexpr (has_to_string<T, std::string()>::value) {
//                return value.to_string();
//            }
//            else if constexpr (std::is_same<bool, T>::value) {
//                return value ? "true" : "false";
//            }
//            else {
                std::stringstream buffer;
                buffer << value;
                return buffer.str();
        //   }
        }

    };

}

#define VarString(variable) (std::string() + #variable + " : " + cu::Log::to_string(variable))

#ifdef UTILS_LOG_ENABLED

#define _Log_0()        cu::Log::log("", __FILE__, __func__, __LINE__)
#define _Log_1(message) cu::Log::log(message, __FILE__, __func__, __LINE__)

#define Separator std::cout << "========================================" << std::endl

#ifdef __cpp_exceptions
#define Fatal(message) { Log(message); throw std::runtime_error(message); };
#else
#define Fatal(message) { Log("### FATAL ERROR ###"); Log(message); std::terminate(); };
#endif

#else

#define _Log_0()
#define _Log_1(message)

#define Separator

#define Fatal(message)

#endif

#define _Log_X(x, A, FUNC, ...) FUNC

#define Log(...) _Log_X(, ##__VA_ARGS__, _Log_1(__VA_ARGS__), _Log_0(__VA_ARGS__))

#define Ping Log();

#define Logvar(variable) Log(VarString(variable))
