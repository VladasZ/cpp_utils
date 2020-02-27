//
//  System.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 8/19/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#pragma once

#include "Path.hpp"

namespace cu {

    struct System {

        static void sleep(double interval);

        static unsigned random();
        static unsigned random(unsigned range);

        static void alert(const std::string& message);

        static const Path& user_name();

        static const Path& home();

        static Path pwd();
        static Path::Array ls(const std::string& path = ".", bool full_path = false);

    };

}

#if __APPLE__
#include "TargetConditionals.h"
#if TARGET_IPHONE_SIMULATOR
#define IOS_SIMULATOR
#elif TARGET_OS_IPHONE
#define IOS_DEVICE
#endif
#endif
