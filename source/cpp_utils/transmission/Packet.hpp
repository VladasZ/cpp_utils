//
//  Packet.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 06/05/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#include "DataUtils.hpp"
#include "PacketHeader.hpp"
#include "PacketFooter.hpp"


namespace cu {

    template<class Data>
    class Packet {

    public:
        const PacketHeader<Data> header { };
    private:
        Data _data;
    public:
        PacketFooter footer { };
        uint8_t endline = '\n';

        void set_data(const Data& data) {
            _data = data;
            footer.checksum = checksum(_data);
        }

        bool checksum_is_valid() const {
            return footer.checksum == checksum(_data);
        }

        const Data& data() const {
            return _data;
        }

    };

}