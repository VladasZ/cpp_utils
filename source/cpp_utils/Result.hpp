//
//  Result.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 9/4/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include "Log.hpp"

namespace cu {

    template<class T>
    class Result {

    public:

        const bool found;
		const bool not_found;
        const T object;

        constexpr Result() : found(false), not_found(!found) {
        }

        constexpr Result(const T& object) : object(object), found(true), not_found(!found) {
        }

        constexpr operator T() const {
            if (!found) {
                throw std::runtime_error(std::string() +
                                         "Conversion of not found result of type: " + typeid(T).name());
            }
            return object;
        }

    };

}
