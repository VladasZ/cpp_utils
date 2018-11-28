//
//  Time.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 9/3/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#pragma once

#include "Singletone.hpp"

class Time : Static {
public:
    static long long now();
    static int interval();
};
