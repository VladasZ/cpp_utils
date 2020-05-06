//
//  PacketHeader.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 06/05/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#include <cstdint>


namespace cu {

    struct _EmptyPacket {
        static inline constexpr uint16_t packet_id = 0;
    };

    template<class Data = _EmptyPacket>
    struct PacketHeader {

        static inline constexpr uint16_t _start_data = 0b1010'0010'0101'0110;

        uint16_t header = _start_data;
        uint16_t size = sizeof(Data);
        uint16_t packet_id = Data::packet_id;

        bool is_valid() const {
            return header == _start_data;
        }

    };

}