//
//  Debug.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 21/01/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#include <functional>

namespace cu {

    class Debug {
    public:
        static void measure(const std::string& file, const std::string& func, int line, std::function<void()> action);
    };

}

#define MEASURE(action) cu::Debug::measure(__FILE__, __func__, __LINE__, action)
