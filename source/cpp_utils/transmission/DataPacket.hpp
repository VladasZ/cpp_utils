//
//  DataPacket.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 13/02/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#include <array>

#include "MetaHelpers.hpp"
#include "PacketHeader.hpp"

namespace cu {

    template <class Data>
    struct DataPacket : public PacketHeader<Data>, public Data {
    };

    template <class  > struct __is_data_packet                 : std::false_type { };
    template <class T> struct __is_data_packet <DataPacket<T>> : std::true_type  { };
    template <class T> constexpr bool is_data_packet_v = __is_data_packet<remove_all_t<T>>::value;

    struct Data { };

    template <class T> constexpr bool is_data_v = std::is_base_of_v<Data, remove_all_t<T>>;

}