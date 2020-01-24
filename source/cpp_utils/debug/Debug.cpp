//
//  Debug.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 21/01/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#include <iostream>

#include "Log.hpp"
#include "Time.hpp"
#include "Debug.hpp"

using namespace cu;
using namespace std;

void Debug::measure(const string& file, const string& func, int line, function<void()> action) {
    const auto stamp = Time::now();
    cout << "Begin" << endl;
    action();
    cout << "End" << endl;
    Log::internal_log("Measure: " + Log::to_string(Time::now() - stamp), file, func, line);
}


