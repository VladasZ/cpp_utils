//
//  Time.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 9/3/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#pragma once

#include <chrono>
#include <cstdint>

namespace cu {

    using nanoseconds  = std::chrono::nanoseconds;
    using milliseconds = std::chrono::milliseconds;
    using seconds      = std::chrono::seconds;
    using minutes      = std::chrono::minutes;
    using hours        = std::chrono::hours;

    template<class T>
    class Time {

    public:

        static inline uint64_t now() {
            return std::chrono::duration_cast<T>(std::chrono::system_clock::now().time_since_epoch()).count();
        }

        static inline uint64_t interval() {
            static uint64_t prev_interval = 1;
            auto result = now() - prev_interval;
            prev_interval = now();
            if (result == 0) return 1;
            return result;
        }

    };

}
