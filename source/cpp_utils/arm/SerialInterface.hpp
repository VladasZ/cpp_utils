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

#include "Packet.hpp"
#include "BoardMessage.hpp"


namespace cu {

    class SerialInterface {

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

        template <class T>
        int write_as_packet(const T& value) {
            static Packet<T> packet;
            packet.set_data(value);
            return write(packet);
        }

        int write_message(const std::string& error) {
            return write_as_packet<BoardMessage>(error);
        }

        bool is_readable() {
            return mbed_serial.readable();
        }

        bool is_writeable() {
            return mbed_serial.writeable();
        }

        bool used = false;

        int read(void* data, int size) {
            wait_for_read();
            used = true;
            return mbed_serial.read(static_cast<uint8_t*>(data), size, [&] (auto) {
                used = false;
            });
            return 0;
        }

        int write(const void* data, int size) {
            wait_for_write();
            used = true;
            return mbed_serial.write(static_cast<const uint8_t*>(data), size, [&](auto) {
                used = false;
            });
            return 0;
        }

        void wait_for_read() {
            while (!is_readable()) { __NOP(); }
            while (used) { __NOP(); }
        }

        void wait_for_write() {
            while (!is_writeable()) { __NOP(); }
            while (used) { __NOP(); }
        }

    };
}

#endif
