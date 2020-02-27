//
//  SystemInfo.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 8/19/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#pragma once

#if __APPLE__
#include "TargetConditionals.h"
#if TARGET_IPHONE_SIMULATOR
#define IOS_SIMULATOR
#elif TARGET_OS_IPHONE
#define IOS_DEVICE
#endif
#endif

#include "Log.hpp"

namespace cu {

    class SystemInfo {

    public:

        static inline constexpr bool is_desktop = [] {
#ifdef DESKTOP_BUILD
            return true;
#else
            return false;
#endif
        }();

        static inline constexpr bool is_ios = [] {
#ifdef IOS_BUILD
            return true;
#else
            return false;
#endif
        }();

        static inline constexpr bool is_android = [] {
#ifdef ANDROID_BUILD
            return true;
#else
            return false;
#endif
        }();

        static inline constexpr bool is_mobile = [] {
            return is_ios || is_android;
        }();

    };

}
