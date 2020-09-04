//
//  PacketHeader.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 06/05/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#include <string>
#include <cstdint>


namespace cu {

    template<class Data>
    struct PacketHeader {

        using StartData = uint16_t;

        static inline const StartData _start_data = 'gb';

        StartData header = _start_data;
        uint16_t data_size = sizeof(Data);

        uint16_t packet_id = Data::packet_id;

        bool is_valid() const {
            return header == _start_data;
        }

        std::string to_string() const {
            return std::to_string(data_size);
        }

    };

    struct _EmptyPacket {
        static inline const uint16_t packet_id = static_cast<uint16_t >(-1);
    };

    using EmptyHeader = PacketHeader<_EmptyPacket>;

}
