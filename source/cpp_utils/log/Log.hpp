//
//  NewLog.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 19/09/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#include <mutex>
#include <string>
#include <iostream>
#include <functional>

#include "Time.hpp"
#include "LogUtils.hpp"
#include "AndroidSystem.hpp"

#ifndef EMBEDDED
#include "File.hpp"
#endif


namespace cu::log {

	struct Settings {
		bool disabled = false;
		bool log_time = false;
		bool log_to_file = false;
		bool log_function_names = false;
		bool temp_disabled = false;
		std::string log_file_name = "cu_log.txt";
		std::function<void(const std::string&)> custom_output = nullptr;
	};

	struct Off {
		bool val;
		Off(bool val) : val(val) { }
		operator bool() const { return val; }
	};

	inline Settings settings;

	class Logger {

	public:

		const Logger& start_log(const std::string& location,
			const std::string& message = "") const {
			if (settings.disabled) return *this;
			settings.temp_disabled = false;
			std::string result_message = "\n";
			if (settings.log_time) {
				result_message += Time::date_time() + " ";
			}
			result_message += location + " ";
			if (!message.empty()) {
				result_message += message + " ";
			}
			system_log(result_message);
			return *this;
		}

		template <class T>
		const Logger& log(const T& val) const {
			if (settings.disabled) return *this;
			if constexpr (std::is_same_v<T, Off>) {
				settings.temp_disabled = val;
			}
			else {
				system_log(log::to_string(val) + " ");
			}
			return *this;
		}

	private:

#ifndef EMBEDDED
		static inline std::once_flag once;
#endif

		static void system_log(const std::string& message) {
			if (settings.disabled || settings.temp_disabled) return;
			if (settings.custom_output) {
				settings.custom_output(message);
			}
			else {
#ifdef ANDROID_BUILD
				AndroidSystem::log(message);
#else
				std::cout << message << std::flush;
#endif
			}
#ifndef EMBEDDED
			if (settings.log_to_file) {
				std::call_once(once, [&] {
					File::remove(settings.log_file_name);
				});
				File::append(settings.log_file_name, message);
			}
#endif
		}

	};

	const inline Logger _logger_instance;

}

template<class T>
const cu::log::Logger& operator<<(const cu::log::Logger& logger, const T& message) {
	if (cu::log::settings.disabled) return logger;
	return logger.log(message);
}

#define Log cu::log::_logger_instance.start_log(CU_LOG_LOCATION)
#define LogMessage(message) cu::log::_logger_instance.start_log(CU_LOG_LOCATION, (message))

#define Fatal(message) { Log << (message); throw std::runtime_error(message); }

#define Logvar(variable) Log << VarString(variable)

#define LogReturn(value) LogMessage("return: " + cu::log::to_string(value)); return value

#define Separator Log << "=========================="
