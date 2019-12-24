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

namespace new_mapping {

    template <class Properties>
    class ClassInfo {

        using _FirstPropertyType = typename std::tuple_element_t<0, Properties>;

        static_assert(cu::is_tuple<Properties>::value);
        static_assert(_FirstPropertyType::is_property);

    public:

        const Properties properties;

        constexpr ClassInfo(Properties props) : properties(props) {
            static_assert(_tuple_is_valid(props));
        }

    private:

        template <class Class>
        static constexpr void _check(bool& value, const Class& param) {
            //Class info constructor accepts only tuple with Property class specializations
            if constexpr (Class::is_property) {
                value = true;
            }
        }

        template <class T>
        static constexpr bool _tuple_is_valid(const T& tuple) {
            bool result = false;
            std::apply([&](auto&&... args) {((
                    _check(result, args)
            ), ...);}, tuple);
            return result;
        }

    };

}
