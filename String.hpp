//
//  String.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 1/30/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#include <string>

namespace String {
    std::string file_name(const std::string& str);
    std::string from_float(float val, int precision = 2);
}



