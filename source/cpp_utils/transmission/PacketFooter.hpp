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

        using EndData = uint16_t;

        static constexpr EndData _end_data = 'ne';

        uint16_t checksum = 0;
        EndData value = _end_data;

        bool is_valid() const { return value == _end_data; }

    };

}
