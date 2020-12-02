//
//  LineID.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 01/12/2020.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

//#define CU_LOG_LOCATION cu::log::location(__FILE__, __func__, __LINE__)

#include <string>

namespace cu {

	class LineID {

	public:

		using str = std::string_view;

		str file;
		str func;
		int line;

		constexpr LineID(str file, str func, int line) : file(file), func(func), line(line) {

		}

	};


}
