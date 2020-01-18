//
//  TypeInfo.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 16/01/2020.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#include <type_traits>

#include "MetaHelpers.hpp"

namespace cu {

    template <class T>
    class TypeInfo {

    public:

        static constexpr auto is_pointer = std::is_pointer_v<T>;

        using Class = cu::remove_all_t<T>;

        static constexpr bool is_string  = std::is_same_v          <Class, std::string>;
        static constexpr bool is_float   = std::is_floating_point_v<Class>;
        static constexpr bool is_integer = std::numeric_limits     <Class>::is_integer;

        static constexpr bool is_std_vector = cu::is_std_vector_v<Class>;

        static constexpr bool is_base_type     = is_string || is_float || is_integer;
        static constexpr bool is_array_type    = is_std_vector;
        static constexpr bool is_embedded_type = is_base_type || is_array_type;
        static constexpr bool is_custom_type   = !is_embedded_type;

        static constexpr bool is_array_of_pointers = [] {
            if constexpr (is_array_type) {
                return std::is_pointer_v<typename Class::value_type>;
            }
            else {
                return false;
            }
        }();

        static constexpr bool is_array_of_embedded_types = [] {
            if constexpr (is_array_type) {
                using ArrayValue = typename Class::value_type;
                using ArrayValueInfo = TypeInfo<ArrayValue>;
                return ArrayValueInfo::is_embedded_type;
            }
            else {
                return false;
            }
        }();

        static constexpr bool is_array_of_custom_types = !is_array_of_embedded_types;

        static std::string to_string() {
            return std::string() +
                   ", is pointer: "               + (is_pointer               ? "true" : "false") + "\n" +
                   ", is array: "                 + (is_array_type            ? "true" : "false") + "\n" +
                   ", is array of custom types: " + (is_array_of_custom_types ? "true" : "false");
        }

    };

}
