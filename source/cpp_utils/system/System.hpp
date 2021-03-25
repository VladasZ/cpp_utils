//
//  System.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 8/19/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#pragma once

#ifdef USE_FULL_LL_DRIVER
#include <stm32f7xx_ll_utils.h>
#else
#include <thread>
#include "Path.hpp"
#endif


namespace cu {

    class System {

    public:

        static void sleep(float interval) {
#ifdef ARDUINO
            delay(1000 * interval);
#elif defined(USE_FULL_LL_DRIVER)
            LL_mDelay(1000 * interval);
#else
            std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<uint64_t>(interval * 1000)));
#endif
        }

        static void alert(const std::string& message);

#ifndef MICROCONTROLLER_BUILD

        static const Path& user_name();

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
