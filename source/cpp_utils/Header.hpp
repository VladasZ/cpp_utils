//
//  Header.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 29/01/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#include <array>

namespace cu {

    template <class T = uint8_t>
    class Header {

        static inline constexpr uint8_t first_byte = 222;
        static inline constexpr uint8_t second_byte = 111;

    public:

        std::array<uint8_t, 2> header = { first_byte, second_byte };
        uint16_t size = sizeof(T);

        bool is_valid() const {
            return header[0] == first_byte && header[1] == second_byte;
        }

        void add_byte(uint8_t byte) {
            auto _data = data();
            _data[0] = _data[1];
            _data[1] = _data[2];
            _data[2] = _data[3];
            _data[3] = byte;
        }

    private:

        uint8_t* data() {
            return &header[0];
        }

    };

}