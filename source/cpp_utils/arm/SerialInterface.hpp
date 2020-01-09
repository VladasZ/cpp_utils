//
//  SerialInterface.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 4/1/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#ifdef MICROCONTROLLER_BUILD

#include <stdint.h>

namespace cu {

    class Serial {

    public:

        template <class T>
        static void write(const T& value) {
            _write(reinterpret_cast<const uint8_t*>(&value), sizeof(value));
        }

    private:

        static void _write(const uint8_t* data, int length);

    };
}

#endif
