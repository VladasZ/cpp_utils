//
//  System.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 8/19/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#pragma once

#include <string>

namespace System {
    void sleep(float interval);
    unsigned int random();
    unsigned random(unsigned int range);
    std::string user_name();
};
