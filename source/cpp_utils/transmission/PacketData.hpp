//
//  PacketHeader.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 07/05/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#include "DataUtils.hpp"
#include "NonCopyable.hpp"
#include "PacketHeader.hpp"
#include "PacketFooter.hpp"

namespace cu {

    class PacketData : NonCopyable {

    public:

        const EmptyHeader header;

        explicit PacketData(const EmptyHeader& header) : header(header) {
            _size = header.data_size + sizeof(PacketFooter);
            _data = new uint8_t[sizeof(EmptyHeader) + _size];
            memcpy(_data, &header, sizeof(EmptyHeader));
        }

        ~PacketData() {
            delete[] _data;
        }

        PacketData(PacketData&& moved) {
            _size = moved._size;
            _data = moved._data;
            moved._size = static_cast<size_t>(-1);
            moved._data = nullptr;
        }

        size_t size() const { return _size; }
        uint8_t* data() { return sizeof(EmptyHeader) + _data; }
        PacketFooter* footer() const {
            return reinterpret_cast<PacketFooter*>(sizeof(EmptyHeader) + header.data_size + _data);
        }

        bool checksum_is_valid() const {
            auto received_summ = checksum(sizeof(EmptyHeader) + _data, header.data_size);
            bool valid = footer()->checksum == received_summ;
            return valid;
        }

    private:

        size_t _size;
        uint8_t* _data;

    };

}