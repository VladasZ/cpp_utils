//
//  FullTypeInfo.hpp
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
    struct FullTypeInfo {

        static constexpr auto is_pointer = std::is_pointer_v<T>;

        using Class = cu::remove_all_t<T>;

        static constexpr bool is_enum = std::is_enum_v<Class>;

        static constexpr bool is_char = std::is_same_v          <Class, char>;
        static constexpr bool is_string = std::is_same_v          <Class, std::string>;
        static constexpr bool is_float = std::is_floating_point_v<Class>;
        static constexpr bool is_integer = std::numeric_limits     <Class>::is_integer || is_enum;

        static constexpr bool is_c_string = is_char && is_pointer;

        static constexpr bool is_std_vector = cu::is_std_vector_v<Class>;

        static constexpr bool is_std_map = cu::is_std_map_v<Class>;

        static constexpr bool is_base_type = is_string || is_float || is_integer;
        static constexpr bool is_array_type = is_std_vector;
        static constexpr bool is_map_type = is_std_map;
        static constexpr bool is_embedded_type = is_base_type || is_array_type || is_map_type;
        static constexpr bool is_custom_type = !is_embedded_type && !is_enum;

        static std::string name() {
            return class_name<Class>;
        }

        static std::string to_string() {
            return std::string() +
                ", is base char: " + (is_char ? "true" : "false") + "\n" +
                ", is is c string: " + (is_c_string ? "true" : "false") + "\n" +
                ", is base type: " + (is_base_type ? "true" : "false") + "\n" +
                ", is embedded type: " + (is_embedded_type ? "true" : "false") + "\n" +
                ", is enum type: " + (is_enum ? "true" : "false") + "\n" +
                ", is custom type: " + (is_custom_type ? "true" : "false") + "\n" +
                ", is pointer: " + (is_pointer ? "true" : "false") + "\n" +
                ", is array: " + (is_array_type ? "true" : "false");
        }

    };

}
