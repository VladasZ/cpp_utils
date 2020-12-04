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
#include <frozen/string.h>

#include "StringUtils.hpp"


namespace cu {

	class FunctionInfo {

		static inline std::unordered_map<size_t, size_t> call_counter;

	public:

		using str = frozen::string;

		constexpr FunctionInfo(str file, str func) : file(file), func(func) {

		}

		void operator++(int) const {
			call_counter[hash()]++;
		}

		size_t call_count() const {
			return call_counter[hash()];
		}

		constexpr std::size_t hash() const {
			return frozen::elsa<str>()(file) +
				   frozen::elsa<str>()(func);
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

	};

}

#define CU_FUN_ID cu::FunctionInfo(__FILE__, __func__)
