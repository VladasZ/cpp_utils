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

#ifdef MICROCONTROLLER_BUILD
    template <class T> std::string class_name = "Not supported on MC";
#else
    template <class T> std::string class_name = typeid(T).name();
#endif

    template <class T, class U> constexpr bool is_same_v = std::is_same_v<remove_all_t<T>, remove_all_t<U>>;

    //MARK: - Pointer to member tools

    template <class           > struct is_pointer_to_member         : std::false_type { };
    template <class T, class U> struct is_pointer_to_member<T U::*> : std::true_type  { };
    template <class T> constexpr bool is_pointer_to_member_v = is_pointer_to_member<remove_all_t<T>>::value;

    template<class T>struct pointer_to_member_class;
    template<class Class, class Value> struct pointer_to_member_class<Value Class::*> { using type = Class; };

    template<class T> struct pointer_to_member_value;
    template<class Class, class Value> struct pointer_to_member_value<Value Class::*> { using type = Value; };

    template <class T>
    struct pointer_to_member_info {
        static_assert(is_pointer_to_member_v<T>);
        using Class = typename pointer_to_member_class<T>::type;
        using Value = typename pointer_to_member_value<T>::type;
    };

    //MARK: - Tuple tools

    template <class     > struct is_tuple                   : std::false_type { };
    template <class ...T> struct is_tuple<std::tuple<T...>> : std::true_type  { };
    template <class T> constexpr bool is_tuple_v = is_tuple<remove_all_t<T>>::value;

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
    constexpr void iterate_tuple(const Tuple& tup, const Lambda& f) {
        static_assert(is_tuple_v<Tuple>);
        cu::static_for<0, std::tuple_size_v<Tuple>>([&](auto i) {
            f(std::get<i.value>(tup));
        });
    }

}
