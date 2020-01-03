//
//  Log.cpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 12/8/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#include <iostream>

#ifdef ANDROID_BUILD
#include <android/log.h>
#endif

#include "Log.hpp"
#include "StringUtils.hpp"

using namespace cu;
using namespace std;

static string last_path_component(const string& path) {
    return (strrchr(path.c_str(), '/') ? strrchr(path.c_str(), '/') + 1 : path.c_str());
}

string Log::location(const string& file, const string& func, int line) {
    string clean_file = cu::String::file_name(last_path_component(file));
    return "[" + clean_file + "::" + func + " - " + to_string(line) + "]";
}

void Log::internal_log(const string& message, const string& file, const string& func, int line) {
    string result_message = location(file, func, line) + " " + message;
#ifdef ANDROID_BUILD
    __android_log_print(ANDROID_LOG_DEBUG, "C++ Log", "%s", result_message.c_str());
#else
    cout << result_message << endl;
#endif
}
