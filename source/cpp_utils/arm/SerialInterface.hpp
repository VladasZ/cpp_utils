//
//  SerialInterface.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 4/1/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#ifdef MICROCONTROLLER_BUILD

namespace cu {
    class Serial {

    public:

        template <class T>
        void serial_write(const T& value) {
            _write(reinterpret_cast<const char*>(&value), sizeof(value));
        }

    private:

        static int _write(const char* data, int length);

    };
}

#endif
