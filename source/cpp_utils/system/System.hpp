//
//  System.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 8/19/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#pragma once

#ifdef ARDUINO
#elif MBED_BUILD
#include <mbed.h>
#elif USE_FULL_LL_DRIVER
#include <stm32f7xx_ll_utils.h>
#else
#include <thread>
#include "Path.hpp"
#endif

#include "Log.hpp"


namespace cu {

    class System {

    public:

        static void sleep(double interval) {
#ifdef ARDUINO
            delay(1000.0 * interval);
#elif MBED_BUILD
            wait_us(1000000.0 * interval);
#elif USE_FULL_LL_DRIVER
            LL_mDelay(1000.0 * interval);
#else
            std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<uint64_t>(interval * 1000)));
#endif
        }

        static unsigned random() {
#ifdef __APPLE__
            return arc4random();
#elif USE_FULL_LL_DRIVER
            return 0;
#else
            static bool first_call = true;
            if (first_call) {
                first_call = false;
                srand(static_cast<unsigned>(time(nullptr)));
            }
            return rand();
#endif
        }

        static unsigned random(unsigned range) {
            return random() % range;
        }

        template <class T>
        static void alert(const T& value) {
            alert(log::to_string(value));
        }

        static void alert(const std::string& message);

#ifndef MICROCONTROLLER_BUILD

        static const Path user_name();

        static const Path& home();

        static Path pwd();
        static std::vector<Path> ls(const std::string& path = ".");

        static void execute(const std::string&);

#endif

#ifdef _WIN32
        static std::vector<std::string> get_com_ports();
#endif

    };

}
