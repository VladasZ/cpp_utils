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
};
