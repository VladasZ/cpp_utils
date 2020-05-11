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
#include "mbed.h"
#else
#include <thread>
#include "Path.hpp"
#endif

namespace cu {

    class System {

    public:

        static void sleep(double interval) {
#ifdef ARDUINO
        delay(1000.0 * interval);
#elif MBED_BUILD
            wait_us(1000000.0 * interval);
            //ThisThread::sleep_for(1000000 * interval);
#else
            std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<uint64_t>(interval * 1000)));
#endif
        }

        static unsigned random() {
#ifdef APPLE
            return arc4random();
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

        static void alert(const std::string& message);

#ifndef MICROCONTROLLER_BUILD

        static const Path user_name();

        static const Path& home();

        static Path pwd();
        static Path::Array ls(const std::string& path = ".", bool full_path = false);

        static void execute(const std::string&);

#endif

    };

}
