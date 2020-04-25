//
//  ForceInitializable.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 02/02/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

namespace cu {

    template <class T>
    class ForceInitializable {
    public:

        template <class Other>
        Other force_convert() const {
            Other result { };
            memcpy(&result, this, sizeof(T));
            return result;
        }

        template <class Other>
        static T force_create(const Other& other) {
            T result;
            memcpy(&result, &other, sizeof(T));
            return result;
        }

    };

}
