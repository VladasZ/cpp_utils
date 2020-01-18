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

static const event_callback_t dummy_callback;

bool cu::SerialInterface::is_readable() {
    return mbed_serial->readable();
}

void cu::SerialInterface::_read(void* data, int size) {
    mbed_serial->read(static_cast<uint8_t*>(data), size, dummy_callback);
}

void cu::SerialInterface::_write(const void* data, int size) {
    mbed_serial->write(static_cast<const uint8_t*>(data), size, dummy_callback);
}

#endif
