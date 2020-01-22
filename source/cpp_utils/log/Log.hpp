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

#define UTILS_LOG_ENABLED

namespace cu {

    class Log {

    public:

        static void internal_log(const std::string& message, const std::string& file, const std::string& func, int line);

        static std::string location(const std::string& file, const std::string& func, int line);

        template <class T>
        static void log(const T& message, const std::string& file, const std::string& func, int line) {
            internal_log(to_string(message), file, func, line);
        }

        template <class T>
        static std::string to_string(const T& value) {
            if constexpr (std::is_same_v<bool, T>) {
                return value ? "true" : "false";
            }
            std::stringstream buffer;
            buffer << value;
            return buffer.str();
        }

    };

}

#define VarString(variable) (std::string() + #variable + " : " + cu::Log::to_string(variable))

#ifdef UTILS_LOG_ENABLED

#define Log(message)  cu::Log::log(message, __FILE__, __func__, __LINE__)
#define Logvar(variable) Log(VarString(variable))

#ifdef __cpp_exceptions
#define Fatal(message) { Log(message); throw std::runtime_error(message); };
#else
#define Fatal(message) { Log("### FATAL ERROR ###"); Log(message); std::terminate(); };
#endif

#else

#define Log(message)
#define Logvar(variable)

#define Fatal(message)

#endif

#define MBED_SERIAL_BAUD 115200

#ifdef MICROCONTROLLER_BUILD
#include "mbed.h"
namespace cu {
    static const auto mbed_serial = [] {
        auto serial = new Serial(USBTX, USBRX);
        serial->baud(MBED_SERIAL_BAUD);
        return serial;
    }();
}
#endif
