//
//  Target.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 11/09/2020.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once


#ifdef _WIN32
#define DESKTOP_BUILD 1
#elif __APPLE__
#include <TargetConditionals.h>
#if TARGET_IPHONE_SIMULATOR
#define IOS_BUILD 1
#elif TARGET_OS_IPHONE
#define IOS_BUILD 1
#elif TARGET_OS_MAC
#define DESKTOP_BUILD 1
#else
#   error "Unknown Apple platform"
#endif
#elif __ANDROID__
#elif __linux__
#define DESKTOP_BUILD 1
#elif ARDUINO
#define EMBEDDED
#elif ESP8266
#define EMBEDDED
#endif