//
//  LogUtils.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 19/08/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#include <string>
#include <sstream>

#include "StringUtils.hpp"
#include "MetaHelpers.hpp"


namespace cu::log {

    template <class T>
    static std::string to_string(const T& value) {
#ifdef ARDUINO
        std::stringstream buffer;
        buffer << value;
        return buffer.str();
#else
        if constexpr (cu::is_std_container_v<T>) {
            if (value.empty()) return "[]";
            std::string result = "[";
            for (auto val : value) {
                result += log::to_string(val) + " ";
            }
            result.pop_back();
            return result + "]";
        }
        else if constexpr (cu::is_std_optional_v<T>) {
            if (value) {
                return to_string(value.value());
            }
            else {
                return "(cu::Log nullopt)";
            }
        }
#ifdef QSTRING_H
        else if constexpr (cu::is_same_v<T, QString>) {
                return value.toStdString();
        }
#endif
#ifdef __OBJC__
        else if constexpr (cu::is_objc_object_v<T>) {
            if (value == nullptr) {
                return "(cu::Log nil)";
            }
            return [[value description] UTF8String];
        }
#endif
        else if constexpr (has_to_string_v<T>) {
            return value.to_string();
        }
        else if constexpr (std::is_pointer_v<T> && has_to_string_v<std::remove_pointer_t<T>>) {
            return value->to_string();
        }
        else if constexpr (std::is_same_v<bool, T>) {
            return value ? "true" : "false";
        }
        else if constexpr (std::is_same_v<std::string, T>) {
            return value.empty() ? "(cu::Log Empty string)" : value;
        }
        else if constexpr (std::is_same_v<std::wstring, T>) {
            return { value.begin(), value.end() };
        }
        else {
            std::stringstream buffer;
            buffer << value;
            return buffer.str();
        }
#endif
    }

    static std::string location(const std::string& file, const std::string& func, int line, bool log_func = true) {
        std::string clean_file = String::last_path_component(file);
        if (clean_file.back() == 'm') {
            return func + " - " + to_string(line) + "] ";
        }
        if (log_func) {
            return "[" + clean_file + "::" + func + " - " + to_string(line) + "]";
        }
        else {
            return "[" + clean_file + " - " + to_string(line) + "]";
        }
    }

}

#define CU_LOG_LOCATION cu::log::location(__FILE__, __func__, __LINE__)

#define VarString(variable) (std::string() + #variable + " : " + cu::log::to_string(variable)) + " "
#define IntString(variable) (std::string() + #variable + " : " + cu::log::to_string(static_cast<int>(variable))) + " "
