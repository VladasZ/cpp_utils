//
//  Time.cpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 9/3/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#include <chrono>

#include "Time.hpp"

using namespace cu;
using namespace std::chrono;


uint64_t Time::now() {
    return duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count();
}

uint64_t Time::interval() {
    static uint64_t prev_interval = 1;
    auto result = now() - prev_interval;
    prev_interval = now();
    if (result == 0) {
        return 1;
    }
    return result;
}
