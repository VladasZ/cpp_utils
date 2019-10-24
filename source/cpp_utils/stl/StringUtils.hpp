//
//  String.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 1/30/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#include <regex>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

namespace cu::String {

[[maybe_unused]]
static std::string file_name(const std::string& str) {
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
        return                                 str.substr(index + 1, len - index - 1);
    }
    return str.substr(index + 1, len - index);
}

[[maybe_unused]]
static std::string from_float(float val, int precision = 2) {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(precision) << val;
    return stream.str();
}

template<class T>
[[maybe_unused]]
static std::string from_container(const T& container) {
    std::string result;
    for (auto val : container)
        result += std::to_string(val) + ", ";
    result.pop_back();
    result.pop_back();
    return result;
}

static std::vector<std::string> find_regexpr_matches(const std::string& string, const std::string& query) {

	std::vector<std::string> result;
	std::regex regex(query);
	std::smatch match;

	std::string::const_iterator searchStart(string.cbegin());
	while (regex_search(searchStart, string.cend(), match, regex)) {
		result.push_back(match[0]);
		searchStart = match.suffix().first;
	}

	return result;
	
}

static std::string find_regexpr_match(const std::string& string, const std::string& query) {
	return find_regexpr_matches(string, query).front();
}

static void drop_first(std::string& string) {
	string.erase(0, 1);
}

static void drop_last(std::string& string) {
	string.erase(string.size() - 1);
}

static void trim(std::string& string) {
	drop_first(string);
	drop_last(string);
}

static std::string& trimmed(std::string& string) {
	trim(string);
	return string;
}

static void replace(const std::string& replace, const std::string& with, std::string& string) {
	for (size_t position = 0;; position += with.length()) {
		position = string.find(replace, position);
		if (position == std::string::npos) {
			break;
		}
		string.erase(position, replace.length());
		string.insert(position, with);
	}
}

}
