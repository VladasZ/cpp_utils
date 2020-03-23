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

    class SerialInterface {

    public:

        template<class T>
        static int read(T& value) {
            return read(&value, sizeof(T));
        }

        template <class T>
        static int write(const T& value) {
            return write(&value, sizeof(T));
        }

        static bool is_readable();
        static bool is_writeable();

        static int read(void* data, int size);
        static int write(const void* data, int size);

    };
}

#endif
