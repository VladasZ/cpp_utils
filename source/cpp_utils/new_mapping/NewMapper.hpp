//
//  NewMapper.hpp
//  mapping
//
//  Created by Vladas Zakrevskis on 24/12/2019.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include <iostream>

#include "Property.hpp"
#include "ClassInfo.hpp"
#include "IterateTuple.hpp"

namespace mapping {

    template <class ClassesInfo>
    class Mapper {

        static_assert(cu::is_tuple<ClassesInfo>::value);

    public:

        const ClassesInfo classes_info;

        constexpr Mapper(const ClassesInfo info) : classes_info(info) {
            static_assert(_tuple_is_valid(info));
        }

        template <class T>
        constexpr bool exists() const {
            bool result = false;
            std::apply([&](auto&&... args) {((
                    _check_if_exists<T>(result, args)
            ), ...);}, classes_info);
            return result;
        }

        std::string to_string() const {
            std::string result;
            cu::iterate_tuple(classes_info, [&](auto info) {
                result += info.to_string() + "\n";
            });
            return result;
        }

    private:

        //MARK: - Tuple Check

        template <class T, class Info>
        constexpr void _check_if_exists(bool& value, const Info& info) const {
            if constexpr (std::is_same_v<T, typename Info::Class>) {
                value = true;
            }
        }

        template <class ClassInfo>
        static constexpr void _check(bool& value, const ClassInfo& param) {
            if constexpr (is_class_info<ClassInfo>::value) {
                value = true;
            }
        }

        template <class T>
        static constexpr bool _tuple_is_valid(const T& tuple) {
            bool result = true;
//            cu::iterate_tuple(tuple, [&](auto info) {
////                if (is_class_info<decltype(info)>::value) {
////                    result = true;
////                }
//            });
            return result;
        }

    };

}
