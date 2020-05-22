//
//  Error.hpp
//  smon
//
//  Created by Vladas Zakrevskis on 18/05/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#include <array>
#include <string>


namespace cu {

    class Error {

        std::array<char, 256> message;

    public:

        static const inline uint16_t packet_id = 200;

        Error() : message({ 0 }) { }

        Error(const std::string& error) {
            strcpy(message.data(), error.c_str());
        }

        operator std::string() const {
            return message.data();
        }

        std::string to_string() const {
            return message.data();
        }

    };

}
