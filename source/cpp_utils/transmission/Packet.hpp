//
//  Packet.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 06/05/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#include "PacketHeader.hpp"


namespace cu {

    template<class Data>
    class Packet {

    public:

        const PacketHeader<Data> header;

        Data data;

        const uint16_t footer = static_cast<uint16_t>(~header._start_data);

    };

}