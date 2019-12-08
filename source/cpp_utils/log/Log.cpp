//
//  Log.cpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 12/8/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#include "Log.hpp"
#include "StringUtils.hpp"

#include <iostream>

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
    cout << result_message << endl;
}

//TODO: - Fix and test
//#ifdef MICROCONTROLLER_BUILD
//#include "mbed.h"
//
//static Serial *serial_transmitter =
//  []{
//	auto serial = new Serial(USBTX, USBRX);
//    serial->baud(230400);
//    return serial;
//  }();
//#endif
