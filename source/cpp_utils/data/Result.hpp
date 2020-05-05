//
//  Result.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 9/4/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include "Log.hpp"
#include "MetaHelpers.hpp"

namespace cu {

    template<class T>
    class Result {

    public:

        const bool found;
		const bool not_found;
        const T object;

        constexpr Result() : found(false), not_found(!found), object(T { }) {
        }

        constexpr Result(const T& object) : object(object), found(true), not_found(!found) {
        }

        constexpr operator T() const {
            if (!found) {
                Fatal("Conversion of not found result of type: " + cu::class_name<T>);
            }
            return object;
        }

    };

}
