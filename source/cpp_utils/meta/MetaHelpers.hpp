//
//  MetaHelpers.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 13/01/2020.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#include <tuple>
#include <type_traits>

namespace cu {

    template <class T> using remove_all_t = std::remove_cv_t<std::remove_reference_t<T>>;


    template <class T> std::string class_name = typeid(T).name();

    template <class     > struct is_tuple                   : std::false_type { };
    template <class ...T> struct is_tuple<std::tuple<T...>> : std::true_type  { };

    template <class T>
    constexpr bool is_tuple_v = is_tuple<remove_all_t<T>>::value;

    template <class           > struct is_pointer_to_member         : std::false_type { };
    template <class T, class U> struct is_pointer_to_member<T U::*> : std::true_type  { };

    template <class T>
    using first_tuple_type = typename std::tuple_element_t<0, T>;

    template <int First, int Last, class Lambda>
    constexpr void static_for(Lambda const& f) {
        if constexpr (First < Last) {
            f(std::integral_constant<int, First> { });
            static_for<First + 1, Last>(f);
        }
    }

    template <class Tuple, class Lambda>
    constexpr void iterate_tuple(Tuple tup, const Lambda& f) {
        static_assert(is_tuple_v<Tuple>);
        cu::static_for<0, std::tuple_size_v<Tuple>>([&](auto i) {
            f(std::get<i.value>(tup));
        });
    }

    template <class Tuple, class Lambda>
    constexpr void iterate_tuple_types(const Lambda& f) {
        static_assert(is_tuple<std::remove_cv_t<Tuple>>::value);
        cu::static_for<0, std::tuple_size_v<Tuple>>([&](auto i) {
            f(std::get<i.value>(std::declval<Tuple>()));
        });
    }

}
