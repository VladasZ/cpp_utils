//
//  Result.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 9/4/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include <string>

#include "JSONMappable.hpp"

namespace cu {

    template<class T>
    class Result {

        static_assert(mapping::is_json_mappable<T> || mapping::is_supported<T>);

    public:

        bool found;
		bool not_found;
        T object;

        Result() : found(false), not_found(!found) {

        }

        Result(const T& object) : object(object), found(true), not_found(!found) {

        }

        operator T() const {
            if (!found) {
                throw std::runtime_error(std::string() +
                                         "Conversion of not found result of type: " + typeid(T).name());
            }
            return object;
        }

        std::string to_string() {
            if (found) {
                return std::string() + "\n" +
                       "Found result: " "\n"
                       + object.to_json();
            }
            return "Not found result";
        }

    };

}
