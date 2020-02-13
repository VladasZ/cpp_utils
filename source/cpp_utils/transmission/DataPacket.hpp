//
//  DataPacket.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 13/02/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#include <array>

#include "PacketHeader.hpp"

namespace cu {

    template <class Data>
    struct DataPacket : public PacketHeader<Data>, public Data {
        using Data::Data;
    };

}