//
//  PacketFooter.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 07/05/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#include "PacketHeader.hpp"


namespace cu {

    struct PacketFooter {

        static constexpr auto _end_data = static_cast<uint16_t>(~EmptyHeader::_start_data);

        uint16_t checksum = 0;
        uint16_t value = _end_data;

        bool is_valid() const { return value == _end_data; }

    };

}
