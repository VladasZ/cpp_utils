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
            return _read(&value, sizeof(T));
        }

        template <class T>
        static int write(const T& value) {
            return _write(&value, sizeof(T));
        }

        static bool is_readable();
        static bool is_writeable();

    private:

        static int _read(void* data, int size);
        static int _write(const void* data, int size);

    };
}

#endif
