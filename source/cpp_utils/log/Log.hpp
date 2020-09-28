//
//  NewLog.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 19/09/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#include <string>
#include <fstream>

#include "File.hpp"
#include "LogUtils.hpp"


namespace cu::log {

    class Logger {

    public:

        const Logger& start_log(const std::string& location,
                                const std::string& message = "") const {
			if (settings.disabled) return *this;
            std::string result_message = "\n" + location + " ";
            if (!message.empty()) {
                result_message += message + " ";
            }
            system_log(result_message);
            return *this;
        }

        template <class T>
        const Logger& log(const T& message) const {
			if (settings.disabled) return *this;
            system_log(log::to_string(message) + " ");
            return *this;
        }

    private:

        void system_log(const std::string& message) const {
			if (settings.disabled) return;
			if (settings.custom_output) {
				settings.custom_output(message);
			}
			else {
				std::cout << message;
			}
            if (settings.log_to_file) {
                static bool first_call = true;
                if (first_call) {
                    first_call = false;
					File::remove(settings.log_file_name);
                }
                File::append(settings.log_file_name, message);
            }
        }

    };

    const inline Logger _logger_instance;

}

template<class T>
inline const cu::log::Logger& operator<<(const cu::log::Logger& logger, const T& message) {
	if (cu::log::settings.disabled) return logger;
    return logger.log(message);
}

#define CU_LOG_LOCATION cu::log::location(__FILE__, __func__, __LINE__)
#define CU_LOG_WITH_LOCATION(message) CU_LOG_LOCATION + " " + (message)

#define Log cu::log::_logger_instance.start_log(CU_LOG_LOCATION)
#define LogMessage(message) cu::log::_logger_instance.start_log(CU_LOG_LOCATION, (message))

#define Fatal(message) { Log << message; throw std::runtime_error(message); }

#define VarString(variable) (std::string() + #variable + " : " + cu::log::to_string(variable)) + " "
#define IntString(variable) (std::string() + #variable + " : " + cu::log::to_string(static_cast<int>(variable))) + " "

#define Logvar(variable) Log << VarString(variable)

#define CleanLog(message) std::cout << cu::log::to_string(message)

#define LogReturn(value) LogMessage("return: " + cu::log::to_string(value)); return value
