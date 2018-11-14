//
//  Time.cpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 9/3/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#include <chrono>

#include "Time.hpp"

using namespace std::chrono;

long long Time::now() {
    long long ms = duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count();
    return ms;
}

int Time::interval() {
    static long long prev_interval = 1;
    int result = int(now() - prev_interval);
    prev_interval = now();
    if (result == 0) return 1;
    return result;
}
