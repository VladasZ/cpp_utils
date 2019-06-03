//
//  LogData.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 1/30/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include <iostream>

namespace cu {

template <class PartType, class DataType>
[[maybe_unused]]
static std::string data_to_string(const DataType& data, size_t new_line = 4) {
    std::string result = "\n";
    static const auto size = sizeof(DataType) / sizeof(PartType);
    auto pointer = reinterpret_cast<const PartType*>(&data);
    for (size_t i = 0; i < size; i++) {
        result += std::to_string(pointer[i]) + " ";
        if ((i + 1) % new_line == 0)
            result += "\n";
    }
    return result;
}

}
