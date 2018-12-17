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

using namespace String;

std::string String::file_name(const std::string& str) {
    if (str.empty()) return "";
    auto len   = str.length();
    auto index = str.find_last_of("/\\");
    if (index == std::string::npos) return str;
	if (index + 1 >= len) {
		len--;
        index = str.substr(0, len).find_last_of("/\\");
        if (len   == 0)                 return str;
        if (index == 0)                 return str.substr(        1, len - 1        );
        if (index == std::string::npos) return str.substr(        0, len            );
                                        return str.substr(index + 1, len - index - 1);
	}
    return str.substr(index + 1, len - index);
}

std::string String::from_float(float val, int precision) {
  std::stringstream stream;
  stream << std::fixed << std::setprecision(precision) << val;
  return stream.str();
}
