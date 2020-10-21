//
//  Range.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 21/10/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#include <string>
#include <limits>

#include "Log.hpp"
#include "MetaHelpers.hpp"


namespace cu {

    template <class T>
    class Range {
	public:

		using Value = T;

		T min;
		T max;

		std::string to_string() const {
			return VarString(min) + "\n" + VarString(max);
		}

    };

}
