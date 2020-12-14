//
//  MetaHelpers.cpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 18/01/2020.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#include "MetaHelpers.hpp"

#ifdef __GNUG__

#include <memory>
#include <cstdlib>
#include <cxxabi.h>

std::string cu::demangle(const std::string& name) {
    int status;
    std::string result = abi::__cxa_demangle(name.c_str(), nullptr, nullptr, &status);
    return (status == 0) ? result : name;
}

#else

std::string cu::demangle(const std::string& name) {
    return name;
}

#endif
