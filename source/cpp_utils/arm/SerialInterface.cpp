//
//  SerialInterface.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 4/1/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#ifdef MICROCONTROLLER_BUILD

#include "mbed.h"

#include "Log.hpp"
#include "SerialInterface.hpp"

using namespace cu;

void cu::Serial::_write(const uint8_t* data, int length) {
    Logvar(length);
    static const event_callback_t dummy_callback;
    mbed_serial->write(data, length, dummy_callback);
}

#endif
