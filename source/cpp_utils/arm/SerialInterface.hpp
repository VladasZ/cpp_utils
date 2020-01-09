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

        template<class T>
        static T& read() {
            static T value;
            value = T { };
            read(value);
            return value;
        }

        template<class T>
        static void read(T& value) {
            _read(&value, sizeof(T));
        }

        template <class T>
        static void write(const T& value) {
            _write(&value, sizeof(value));
        }

    private:

        static void _read(void* data, int size);
        static void _write(const void* data, int size);

    };
}

#endif
