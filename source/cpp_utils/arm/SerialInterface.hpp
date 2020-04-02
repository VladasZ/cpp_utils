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

#include <mbed.h>

namespace cu {

    class SerialInterface {

        const event_callback_t dummy_callback;

        Serial& mbed_serial;

    public:

        SerialInterface(Serial& mbed_serial) : mbed_serial(mbed_serial) { }

        template<class T>
        int read(T& value) {
            return read(&value, sizeof(T));
        }

        template <class T>
        int write(const T& value) {
            return write(&value, sizeof(T));
        }

        bool is_readable(){
            return mbed_serial.readable();
        }

        bool is_writeable()  {
            return mbed_serial.writeable();
        }

        int read(void* data, int size){
            return mbed_serial.read(static_cast<uint8_t*>(data), size, dummy_callback);
        }

        int write(const void* data, int size) {
            return mbed_serial.write(static_cast<const uint8_t*>(data), size, dummy_callback);
        }

    };
}

#endif
