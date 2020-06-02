//
//  SerialInterface.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 4/1/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#ifdef USE_FULL_LL_DRIVER

#include <stdint.h>

#include "UART.hpp"
#include "Packet.hpp"
#include "BoardMessage.hpp"


namespace cu {

    class SerialInterface {

    public:

        template<class T>
        bool get(T& value) {
            return UART::get(value);
        }

        template <class T>
        void write(const T& value) {
            UART::write(value);
        }

        template <class T>
        void write_as_packet(const T& value) {
            static Packet<T> packet;
            packet.set_data(value);
            write(packet);
        }

        void write_message(const std::string& message) {
            write_as_packet<BoardMessage>(message);
        }

    };
}

#endif
