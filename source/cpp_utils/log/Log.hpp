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
//#define UTILS_LOG_FUNCTION_NAMES

#ifdef STM32_F7
#include <stm32f7xx_ll_utils.h>
#endif
#ifdef MICROCONTROLLER_BUILD
__weak void __cu_log_print_impl(const std::string&);
#endif

namespace cu {

    class Log {

    public:

        static std::string last_path_component(const std::string& path) {
#ifdef WINDOWS_BUILD
            static const char slash = '\\';
#else
            static const char slash = '/';
#endif
            auto pos = strrchr(path.c_str(), slash);
            return pos ? pos + 1 : path;
        }

        static void internal_log(const std::string& message, const std::string& file, const std::string& func, int line) {
            std::string result_message = location(file, func, line) + " " + message;
#ifdef ARDUINO
            Serial.println(result_message.c_str());
#elif ANDROID_BUILD
            __android_log_print(ANDROID_LOG_DEBUG, "C++ Log", "%s", result_message.c_str());
#elif MICROCONTROLLER_BUILD
            __cu_log_print_impl(result_message);
#else
            std::cout << result_message << std::endl;
#endif
        }

        static std::string location(const std::string& file, const std::string& func, int line) {
            std::string clean_file = last_path_component(file);
            if (clean_file.back() == 'm') {
                return func + " - " + to_string(line) + "] ";
            }
#ifdef UTILS_LOG_FUNCTION_NAMES
            return "[" + clean_file + "::" + func + " - " + to_string(line) + "]";
#else
            return "[" + clean_file + " - " + to_string(line) + "]";
#endif
        }

        template <class T>
        static void log(const T& message, const std::string& file, const std::string& func, int line) {
            internal_log(to_string(message), file, func, line);
        }

        template <class T>
        static std::string to_string(const T& value) {
#ifdef ARDUINO
            std::stringstream buffer;
            buffer << value;
            return buffer.str();
#else
            if constexpr (cu::is_std_container_v<T>) {
                if (value.empty()) return "[]";
                std::string result = "[";
                for (auto val : value) {
                    result += Log::to_string(val) + " ";
                }
                result.pop_back();
                return result + "]";
            }
            else if constexpr (cu::is_std_optional_v<T>) {
                if (value) {
                    return to_string(value.value());
                }
                else {
                    return "(cu::Log nullopt)";
                }
            }
#ifdef QSTRING_H
            else if constexpr (cu::is_same_v<T, QString>) {
                return value.toStdString();
            }
#endif
#ifdef __OBJC__
            else if constexpr (cu::is_objc_object_v<T>) {
                if (value == nullptr) {
                    return "(cu::Log nil)";
                }
                return [[value description] UTF8String];
            }
#endif
            else if constexpr (has_to_string_v<T>) {
                return value.to_string();
            }
            else if constexpr (std::is_same_v<bool, T>) {
                return value ? "true" : "false";
            }
            else if constexpr (std::is_same_v<std::string, T>) {
                if (value.empty()) return "(cu::Log Empty string)";
                return value;
            }
            else {
                std::stringstream buffer;
                buffer << value;
                return buffer.str();
            }
#endif
        }
    };

}

#define VarString(variable) (std::string() + #variable + " : " + cu::Log::to_string(variable))
#define IntString(variable) (std::string() + #variable + " : " + cu::Log::to_string(static_cast<int>(variable)))

#ifdef UTILS_LOG_ENABLED

#define Log(message) cu::Log::log(message, __FILE__, __func__, __LINE__)
#define LogInt(message) Log(IntString(message))
#define CleanLog(message) std::cout << cu::Log::to_string(message) << std::endl;

#define Separator Log("========================================")

#ifdef __cpp_exceptions
#define Fatal(message) { Log(message); throw std::runtime_error(message); };
#else
#define Fatal(message) { Log("### FATAL ERROR ###"); Log(message); std::terminate(); };
#endif

#else

#define Separator

#define Log(message)
#define CleanLog(message)
#define Fatal(message)

#endif


#define Ping Log("");

#define Logvar(variable) Log(VarString(variable))
