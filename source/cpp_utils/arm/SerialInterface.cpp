//
//  SerialInterface.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 4/1/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#ifdef MICROCONTROLLER_BUILD

#include "Log.hpp"
#include "SerialInterface.hpp"

using namespace cu;

int cu::Serial::_write(const char* data, int length) {
    static const event_callback_t dummy_callback = [](int a) {
        Log("Hello");
        Logvar(a);
    };
    serial_transmitter->write(reinterpret_cast<const uint8_t*>(data), length, dummy_callback);
}

#endif
