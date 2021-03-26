//
//  StringUtils.cpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 9/01/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#include <regex>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

#include "Log.hpp"
#include "StringUtils.hpp"

using namespace cu;
using namespace std;


string String::file_name(const string& str) {
    if (str.empty()) return "";
    auto len   = str.length();
    auto index = str.find_last_of("/\\");
    if (index == string::npos) return str;
    if (index + 1 >= len) {
        len--;
        index = str.substr(0, len).find_last_of("/\\");
        if (len   == 0)            return str;
        if (index == 0)            return str.substr(        1, len - 1        );
        if (index == string::npos) return str.substr(        0, len            );
        return                            str.substr(index + 1, len - index - 1);
    }
    return str.substr(index + 1, len - index);
}

string String::from_float(float val, int precision) {
    stringstream stream;
    stream << fixed << setprecision(precision) << val;
    return stream.str();
}

string String::find_regexpr_match(const string& str, const string& query) {
    auto matches = find_regexpr_matches(str, query);
    if (matches.empty()) {
        Log << "No match for:" << query << "in" << str;
        return "";
    }
    return matches.front();
}

vector<string> String::find_regexpr_matches(const string& str, const string& query) {

    vector<string> result;
    regex regex(query);
    smatch match;

    string::const_iterator searchStart(str.cbegin());
    while (regex_search(searchStart, str.cend(), match, regex)) {
        result.push_back(match[0]);
        searchStart = match.suffix().first;
    }

    return result;

}

string String::from_bool(bool value) {
    return value ? "true" : "false";
}

bool String::contains(const string& str, const string& part, bool case_sensetive) {
    if (case_sensetive) {
        return str.find(part) != string::npos;
    }
    return to_lower(str).find(to_lower(part)) != string::npos;
}

string String::remove(const string& str, char symbol) {
    string result = str;
    result.erase(remove_if(result.begin(),
                           result.end(),[=](char c) { return c == symbol; }),
                 result.end());
    return result;
}

void String::drop_first(string& str, size_t count) {
    str.erase(0, count);
}

void String::drop_last(string& str, size_t count) {
    str.erase(str.size() - count);
}

void String::trim(string& str) {
    drop_first(str);
    drop_last(str);
}

string& String::trimmed(string& str) {
    trim(str);
    return str;
}

void String::replace(char replace, char with, std::string& string) {
    for (auto& c : string) {
        if (c == replace) {
            c = with;
        }
    }
}

void String::replace(const string& replace, const string& with, string& str) {
    for (size_t position = 0;; position += with.length()) {
        position = str.find(replace, position);
        if (position == string::npos) {
            break;
        }
        str.erase(position, replace.length());
        str.insert(position, with);
    }
}

string String::to_lower(const string& str) {
    string result;
    for (auto c : str) {
        result += static_cast<char>(tolower(c));
    }
    return result;
}

string String::all_chars() {
    string result;
    for (char i = 0; i < 127; i++) {
        result += i;
    }
    return result;
}

string String::only_letters(const string& str) {
    string result;
    for (auto ch : str) {
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
            result.push_back(ch);
    }
    return result;
}