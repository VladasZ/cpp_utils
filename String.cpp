//
//  String.cpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 1/30/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#include <iomanip>
#include <sstream>

#include "String.hpp"

String String::file_name() const {
	if (empty()) return "";
	auto len   = length();
	auto index = find_last_of("/\\");
	if (index == std::string::npos) return *this;
	if (index + 1 >= len) {
		len--;
		index = substr(0, len).find_last_of("/\\");
		if (len   == 0)                 return *this;
		if (index == 0)                 return substr(        1, len - 1        );
		if (index == std::string::npos) return substr(        0, len            );
		                                return substr(index + 1, len - index - 1);
	}
	return substr(index + 1, len - index);
}

String String::from_float(float val, int precision) {
  std::stringstream stream;
  stream << std::fixed << std::setprecision(precision) << val;
  return stream.str();
}
