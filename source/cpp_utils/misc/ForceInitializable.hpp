//
//  ForceInitializable.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 02/02/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

namespace cu {

    template <class To, class From>
    static inline constexpr To force_convert(const From& from) {
        static_assert(sizeof(From) == sizeof(To));
        To result{ };
        memcpy(&result, &from, sizeof(To));
        return result;
    }

}