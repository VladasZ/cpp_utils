////
////  Log.hpp
////  cpp_utils
////
////  Created by Vladas Zakrevskis on 12/8/19.
////  Copyright © 2019 VladasZ. All rights reserved.
////
//
//#pragma once
//
//#include <string>
//#include <cstring>
//#include <sstream>
//#include <iostream>
//
//#ifdef ARDUINO
//#include <HardwareSerial.h>
//#else
//#include "MetaHelpers.hpp"
//#endif
//
//#include "LogUtils.hpp"
//
//#define UTILS_LOG_ENABLED
//#define UTILS_LOG_FUNCTION_NAMES
//
//#ifdef STM32_F7
//#include <stm32f7xx_ll_utils.h>
//#endif
//
//#ifdef CU_CUSTOM_LOG_OUTPUT
//[[weak]] void __cu_log_print_impl(const std::string&);
//#endif
//
//#ifdef CU_LOG_TO_FILE
//#include "NewPath.hpp"
//#endif
//
//namespace cu {
//
//    class Log {
//
//    public:
//
//        static inline void internal_log(const std::string& message, const std::string& file, const std::string& func, int line) {
//            std::string result_message = log::location(file, func, line) + " " + message;
//#ifdef CU_CUSTOM_LOG_OUTPUT
//            __cu_log_print_impl(result_message);
//#elif ANDROID_BUILD
//            __android_log_print(ANDROID_LOG_DEBUG, "C++ Log", "%s", result_message.c_str());
//#elif ARDUINO
//            Serial.println(result_message.c_str());
//#else
//            std::cout << result_message << std::endl;
//#ifdef CU_LOG_TO_FILE
//            static bool first_call = true;
//            static const std::string log_file = "cu_log.txt";
//            if (first_call) {
//                first_call = false;
//                NewPath::remove(log_file);
//            }
//            NewPath::write(log_file, result_message);
//#endif
//#endif
//        }
//
//        template <class T>
//        static void log(const T& message, const std::string& file, const std::string& func, int line) {
//            internal_log(log::to_string(message), file, func, line);
//        }
//    };
//
//}
//

//
//#ifdef UTILS_LOG_ENABLED
//
//#define Log(message) cu::Log::log(message, __FILE__, __func__, __LINE__)
//#define LogInt(message) Log(IntString(message))
//#define CleanLog(message) std::cout << cu::log::to_string(message) << std::endl;
//
//#define SeparatorLine Log("========================================")
//
//#ifdef __cpp_exceptions
//#define Fatal(message) { Log(message); throw std::runtime_error(message); };
//#else
//#define Fatal(message) { Log("### FATAL ERROR ###"); Log(message); std::terminate(); };
//#endif
//
//#else
//
//#define Separator
//
//#define Log(message)
//#define CleanLog(message)
//#define Fatal(message)
//
//#endif
//
//
//#define Ping Log("");
//
//#define Logvar(variable) Log(VarString(variable))
