//
//  FilesystemInclude.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 09/10/2020.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#ifndef __MINGW32__

    #if __has_include(<filesystem>)
        #include <filesystem>
    #endif

#endif
