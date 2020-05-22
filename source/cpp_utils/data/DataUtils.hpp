//
//  DataUtils.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 06/05/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#include <array>
#include <string>


namespace cu {

    template <class T>
    static void wipe(T& data) {
        memset(&data, 0, sizeof(T));
    }

    template <class T>
    static void push_byte(T& data, uint8_t byte) {
        auto ptr = reinterpret_cast<uint8_t*>(&data);
        for (int i = 0; i < sizeof(data); i++) {
            ptr[i] = ptr[i + 1];
        }
        ptr[sizeof(data) - 1] = byte;
    }

    template <class T>
    static std::string byte_string(const T& data) {
        std::string result = "[";
        auto ptr = reinterpret_cast<const uint8_t*>(&data);
        for (int i = 0; i < sizeof(data); i++) {
            result += std::to_string(static_cast<int>(ptr[i])) + " ";
        }
        result.pop_back();
        return result + "]";
    }

    template <class T, class U>
    static void assign(T& var, const U& val) {
        var = static_cast<T>(val);
    }

}
