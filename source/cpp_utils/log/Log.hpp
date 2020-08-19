//
//  NewLog.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 19/09/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#include <string>

#include "LogUtils.hpp"


namespace cu::log {

    class Logger {

    public:

        Logger& start_log(const std::string& file, const std::string& func, int line) {
            system_log("\n" + log::location(file, func, line) + " ");
            return *this;
        }

        template <class T>
        Logger& log(const T& message) {
            system_log(log::to_string(message) + " ");
            return *this;
        }

    private:

        void system_log(const std::string& message) {
            std::cout << message;
        }

    };

    static inline Logger _logger_instance;

}

template<class T>
inline cu::log::Logger& operator<<(cu::log::Logger& logger, const T& message) {
    logger.log(message);
    return logger;
}

#define Log cu::log::_logger_instance.start_log(__FILE__, __func__, __LINE__)
#define Fatal(message) { Log << message; throw std::runtime_error(message); };

#define VarString(variable) (std::string() + #variable + " : " + cu::log::to_string(variable))
#define IntString(variable) (std::string() + #variable + " : " + cu::log::to_string(static_cast<int>(variable)))

#define Logvar(variable) Log << VarString(variable)

#define CleanLog(message) std::cout << cu::log::to_string(message) << std::endl;
