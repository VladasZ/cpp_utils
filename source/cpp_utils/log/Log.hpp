//
//  Log.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 12/8/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include <string>
#include <sstream>
#include <iostream>

#include "MetaHelpers.hpp"

#define UTILS_LOG_ENABLED

namespace cu {

    class Log {

    public:

        static std::string last_path_component(const std::string& path);

        static void internal_log(const std::string& message, const std::string& file, const std::string& func, int line);

        static std::string location(const std::string& file, const std::string& func, int line);

        template <class T>
        static void log(const T& message, const std::string& file, const std::string& func, int line) {
            internal_log(to_string(message), file, func, line);
        }

        template <class T>
        static std::string to_string(const T& value) {
            if constexpr (cu::is_std_vector_v<T>) {
                std::string result = "\n";
                for (auto val : value) {
                    result += Log::to_string(val) + "\n";
                }
                return result;
            }
#ifdef __OBJC__
            else if constexpr (cu::is_objc_object_v<T>) {
                if (value == nullptr) {
                    return "nil";
                }
                return [[value description] cString];
            }
#endif
            else if constexpr (has_to_string<T, std::string()>::value) {
                return value.to_string();
            }
            else if constexpr (std::is_same<bool, T>::value) {
                return value ? "true" : "false";
            }
            else {
                std::stringstream buffer;
                buffer << value;
                return buffer.str();
            }
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


#define MBED_SERIAL_BAUD 115200

#ifdef MBED_BUILD
#include "mbed.h"
namespace cu {
    static const auto mbed_serial = [] {
        auto serial = new Serial(USBTX, USBRX);
        serial->baud(MBED_SERIAL_BAUD);
        return serial;
    }();
}
#endif

#undef constexpr
