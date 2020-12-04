//
//  LineID.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 01/12/2020.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#include <string>
#include <unordered_map>

#include "StringUtils.hpp"


namespace cu {

	class LineID {

		static inline std::unordered_map<size_t, size_t> call_counter;

	public:

		using str = std::string_view;

		constexpr LineID(str file, str func, int line) : file(file), func(func), line(line) {

		}

		std::string location(bool log_func = true) const {
			auto clean_file = this->clean_file();
			if (clean_file.back() == 'm') {
				return "[" + func_string() + " - " + std::to_string(line) + "] ";
			}
			if (log_func) {
				return "[" + clean_file + "::" + func_string() + " - " + std::to_string(line) + "]";
			}
			else {
				return "[" + clean_file + " - " + std::to_string(line) + "]";
			}
		}

		void operator++(int) const {
			call_counter[hash()]++;
		}

		size_t call_count() const {
			return call_counter[hash()];
		}

		std::size_t hash() const {
			return std::hash<str>()(file) +
				   std::hash<str>()(func) +
			       line;
		}

	private:

		std::string file_string() const {
			return { file.data(), file.size() };
		}

		std::string func_string() const {
			return { func.data(), func.size() };
		}

		std::string clean_file() const {
			return String::last_path_component(file_string());
		}

	private:

		str file;
		str func;
		int line;

	};

}

#define CU_LINE_ID cu::LineID(__FILE__, __func__, __LINE__)
