//
//  StringUtils.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 1/30/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#include <vector>
#include <string>

namespace cu::String {

    std::string file_name(const std::string& str);

    std::string from_float(float val, int precision = 2);

    std::string find_regexpr_match(const std::string& string, const std::string& query);

    std::vector<std::string> find_regexpr_matches(const std::string& string, const std::string& query);

    std::string from_bool(bool value);

    bool contains(const std::string& string, const std::string& part);

    std::string remove(const std::string& string, char symbol);

    void drop_first(std::string& string, unsigned count = 1);

    void drop_last(std::string& string, unsigned count = 1);

    void trim(std::string& string);

    std::string& trimmed(std::string& string);

    void replace(char replace, char with, std::string& string);
    void replace(const std::string& replace, const std::string& with, std::string& string);

    std::string to_lower(const std::string& string);

    template<class T>
    static std::string from_container(const T& container) {
        if (container.empty()) return "[]";
        std::string result = "[";
        for (const auto& val : container) {
            result += std::to_string(val) + ", ";
        }
        result.pop_back();
        result.pop_back();
        return result + "]";
    }

}
