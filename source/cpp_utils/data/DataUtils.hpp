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

#include "MetaHelpers.hpp"


namespace cu {

    template <class T>
    void wipe(T& data) {
        memset(&data, 0, sizeof(T));
    }

    template <class T>
    void add_byte(T& data, uint8_t byte) {
        auto ptr = reinterpret_cast<uint8_t*>(&data);
        for (int i = 0; i < sizeof(data); i++) {
            ptr[i] = ptr[i + 1];
        }
        ptr[sizeof(data) - 1] = byte;
    }

}
