//
//  FilesystemInclude.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 09/10/2020.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#include "Target.hpp"

#ifndef __MINGW32__

    #ifdef ANDROID_BUILD

    #elif __has_include(<filesystem>)
        #include "Target.hpp"
        #ifdef IOS_BUILD
        #else
            #include <filesystem>
            #define CU_USING_FILESYSTEM
        #endif
    #endif

#endif
