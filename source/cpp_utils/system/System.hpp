//
//  System.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 8/19/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#pragma once

#include "Path.hpp"
#include "SystemInfo.hpp"

namespace cu {

    class System {

    public:

        static void sleep(double interval);

        static unsigned random();
        static unsigned random(unsigned range);

        static void alert(const std::string& message);

        static const Path user_name();

        static const Path& home();

        static Path pwd();
        static Path::Array ls(const std::string& path = ".", bool full_path = false);

    };

}
