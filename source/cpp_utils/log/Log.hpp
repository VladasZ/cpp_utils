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

namespace cu {

    class Log {

        static void internal_log(const std::string& message, const std::string& file, const std::string& func, int line);


    public:

        static std::string location(const std::string& file, const std::string& func, int line);

        template <class T>
        static void log(const T& message, const std::string& file, const std::string& func, int line) {
            internal_log(to_string(message), file, func, line);
        }

        template <class T>
        static std::string to_string(const T& value) {
            std::stringstream buffer;
            if constexpr (std::is_same_v<bool, T>) {
                buffer << (value ? "true" : "false");
            }
            else {
                buffer << value;
            }
            return buffer.str();
        }

    };

}

#define __UTILS_INTERNAL_LOG(message, file, func, line) cu::Log::log(message, file, func, line)

#define Log(message)  __UTILS_INTERNAL_LOG (message, __FILE__, __func__, __LINE__)
#define Logvar(variable) Log(std::string() + #variable + " : " + cu::Log::to_string(variable))

#define Fatal(message) { Log(message); throw std::runtime_error(message);  };


#ifdef MICROCONTROLLER_BUILD
#include "mbed.h"

static Serial *serial_transmitter =
 []{
	auto serial = new Serial(USBTX, USBRX);
   serial->baud(230400);
   return serial;
 }();
#endif
