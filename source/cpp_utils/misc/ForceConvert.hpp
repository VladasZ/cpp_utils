//
//  ForceConvert.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 02/02/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once


namespace cu {

    template <class To, class From>
    static inline const To& cast(const From& from) {
        static_assert(sizeof(From) == sizeof(To));
        return reinterpret_cast<const To&>(from);
    }

    template <class To, class From>
    static inline const To& force_cast(const From& from) {
        return reinterpret_cast<const To&>(from);
    }
    
}
