//
//  MetaHelpers.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 13/01/2020.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#include <tuple>
#include <vector>
#include <string>
#include <type_traits>


namespace cu {

    std::string demangle(const std::string& name);

    template <class T> using remove_all_t = std::remove_cv_t<std::remove_reference_t<std::remove_pointer_t<T>>>;

#ifdef MICROCONTROLLER_BUILD
    template <class T> std::string class_name = "Not supported on MC. sizeof: " + std::to_string(sizeof(T));
#else
    template <class T> std::string class_name = demangle(typeid(T).name());
#endif

    template <class T, class U> constexpr bool is_same_v = std::is_same_v<remove_all_t<T>, remove_all_t<U>>;
    template <class T, class U> constexpr bool is_base_of_v = std::is_base_of_v<remove_all_t<T>, remove_all_t<U>>;

    template <class  > struct __is_vector                 : std::false_type { };
    template <class T> struct __is_vector<std::vector<T>> : std::true_type  { };
    template <class T> constexpr bool is_std_vector_v = __is_vector<remove_all_t<T>>::value;

    //MARK: - Pointer to member tools

    template <class           > struct __is_pointer_to_member         : std::false_type { };
    template <class T, class U> struct __is_pointer_to_member<T U::*> : std::true_type  { };
    template <class T> constexpr bool is_pointer_to_member_v = __is_pointer_to_member<remove_all_t<T>>::value;

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

    template <class     > struct __is_tuple                   : std::false_type { };
    template <class ...T> struct __is_tuple<std::tuple<T...>> : std::true_type  { };
    template <class T> constexpr bool is_tuple_v = __is_tuple<remove_all_t<T>>::value;

    template <class T>
    using first_tuple_type = typename std::tuple_element_t<0, T>;

    template <int First, int Last, class Lambda>
    constexpr void static_for(const Lambda& f) {
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

#include <type_traits>

// Primary template with a static assertion
// for a meaningful error message
// if it ever gets instantiated.
// We could leave it undefined if we didn't care.

    template<typename, typename T>
    struct has_to_string {
        static_assert(
                std::integral_constant<T, false>::value,
                "Second template parameter needs to be of function type.");
    };

// specialization that does the checking

    template<typename C, typename Ret, typename... Args>
    struct has_to_string<C, Ret(Args...)> {
    private:
        template<typename T>
        static constexpr auto check(T*) -> typename
        std::is_same<
                decltype( std::declval<T>().to_string( std::declval<Args>()... ) ),
                Ret    // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
        >::type;  // attempt to call it and see if the return type is correct

        template<typename>
        static constexpr std::false_type check(...);

        typedef decltype(check<C>(0)) type;

    public:
        static constexpr bool value = type::value;
    };

}
