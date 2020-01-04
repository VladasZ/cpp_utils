//
//  I2CMaster.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 7/1/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include "System.hpp"

#ifdef MICROCONTROLLER_BUILD

namespace cu {

    class I2CMaster {

        int _current_address = 0;
        void* _interface;

    public:

        I2CMaster(PinName sda, PinName scl);

        void set_write_address(int);

        int write_string(const std::string&);

        template <class T>
        int write(const T& data) {
            return _write(reinterpret_cast<const char*>(&data), sizeof(T));
        }

        int read(char* data, int length);

    private:

        int _write(const char* data, int length);

    };

}

#endif
