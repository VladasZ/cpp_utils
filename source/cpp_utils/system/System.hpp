//
//  System.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 8/19/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#pragma once

#include "Path.hpp"

namespace cu::System {
    void sleep(float interval);
    unsigned random();
    unsigned random(unsigned range);
    Path user_name();
	void alert(const std::string& message);
}

#if __APPLE__
#include "TargetConditionals.h"
#if TARGET_IPHONE_SIMULATOR
#define IOS_SIMULATOR
#elif TARGET_OS_IPHONE
#define IOS_DEVICE
#endif
#endif

#ifdef __arm__
#if __APPLE__
#else
#ifndef __ANDROID__
#define MICROCONTROLLER_BUILD
#endif
#endif
#endif
