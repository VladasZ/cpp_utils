//
//  Path.cpp
//  cpp_tools
//
//  Created by Vladas Zakrevskis on 8/6/19.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#include "Path.hpp"

using namespace cu;

Path::Path(const std::string& str) : std::string(str) {
    
}

Path Path::operator / (const Path& path) const {
    auto result = *this;
    result += "/";
    result += path;
    return result;
}
