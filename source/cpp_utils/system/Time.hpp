//
//  Time.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 9/3/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#pragma once

#include <ctime>
#include <string>
#include <chrono>
#include <cstdint>


namespace cu {

    using nanoseconds  = std::chrono::nanoseconds;
    using milliseconds = std::chrono::milliseconds;
    using seconds      = std::chrono::seconds;
    using minutes      = std::chrono::minutes;
    using hours        = std::chrono::hours;

    class Time {

		static inline uint64_t prev_interval = 1;

    public:

        static inline uint64_t now() {
            return std::chrono::duration_cast<nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        }

        static inline uint64_t interval() {
            auto result = now() - prev_interval;
            prev_interval = now();
            if (result == 0) return 1;
            return result;
        }

		static inline std::string date_time() {
			auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
			return std::ctime(&time);
		}

    };

}
