//
//  BoardMessage.hpp
//  smon
//
//  Created by Vladas Zakrevskis on 18/05/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#include <array>
#include <string>
#include <cstring>


namespace cu {

    class BoardMessage {

        static inline const size_t size = 256;

        std::array<char, size> message { 0 };

    public:

        static const inline uint16_t packet_id = 200;

        BoardMessage() : message({ 0 }) { }

        BoardMessage(const std::string& error) {
#ifdef _WINDOWS
			strcpy_s(message.data(), error.size() + 1, error.c_str());
#else
            strcpy(message.data(), error.c_str());
#endif
        }

        operator std::string() const {
            return message.data();
        }

        std::string to_string() const {
            return message.data();
        }

    };

}
