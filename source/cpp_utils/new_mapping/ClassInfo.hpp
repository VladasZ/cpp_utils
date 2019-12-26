//
//  ClassInfo.hpp
//  mapping
//
//  Created by Vladas Zakrevskis on 24/12/2019.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include <iostream>

#include "IterateTuple.hpp"

namespace mapping {

    template <class Properties>
    class ClassInfo {

        using _FirstPropertyType = typename std::tuple_element_t<0, Properties>;

        static_assert(cu::is_tuple<Properties>::value);
        static_assert(is_property<_FirstPropertyType>::value);

    public:

        static constexpr bool is_class_info = true;

        using Class = typename _FirstPropertyType::Class;

        const std::string_view name;
        const Properties properties;

        constexpr ClassInfo(const std::string_view name, const Properties props) : name(name), properties(props) {
            static_assert(_tuple_is_valid(props));
        }

        std::string to_string() const {
            std::string result = std::string(name) + "\n";
            cu::iterate_tuple(properties, [&](auto prop){
                result += prop.to_string() + "\n";
            });
            return result;
        }

    private:

        //MARK: - Tuple Check

        template <class Property>
        static constexpr void _check(bool& value, const Property& param) {
            if constexpr (is_property<Property>::value) {
                value = true;
            }
            static_assert(std::is_same_v<typename _FirstPropertyType::Class, typename Property::Class>);
        }

        template <class T>
        static constexpr auto _tuple_is_valid(const T& tuple) {
            bool result = false;
            std::apply([&](auto&&... args) {((
                    _check(result, args)
            ), ...);}, tuple);
            return result;
        }

    };

    template <class  > struct is_class_info               : std::false_type { };
    template <class T> struct is_class_info<ClassInfo<T>> : std::true_type  { };

}
