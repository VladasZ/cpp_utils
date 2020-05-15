//
//  Packet.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 06/05/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#include "NonCopyable.hpp"
#include "PacketHeader.hpp"
#include "PacketFooter.hpp"


namespace cu {

    template<class Data>
    class Packet : NonCopyable {

    public:
        const PacketHeader<Data> header { };
    private:
        Data _data;
    public:
        const PacketFooter footer { };

        void set_data(const Data& data) {
            _data = data;
        }

        const Data& data() const {
            return _data;
        }

    };

}