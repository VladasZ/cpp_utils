//
//  MetaHelpers.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 13/01/2020.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#include <map>
#include <list>
#include <tuple>
#include <vector>
#include <string>
#include <type_traits>

#include "STDExperimental.hpp"


namespace cu {

    std::string demangle(const std::string& name);

    template <class T> using remove_all_t = std::remove_cv_t<std::remove_reference_t<std::remove_pointer_t<T>>>;

#ifndef EMBEDDED
    template <class T> std::string class_name() { return demangle(typeid(T).name()); }
    template <class T> std::string class_name(const T& obj) { return class_name<T>(); }

#define CU_CLASS_NAME(type) class_name<type>()
#endif

    template <class T, class U> constexpr bool is_same_v = std::is_same<cu::remove_all_t<T>, cu::remove_all_t<U>>::value;

    template <class T, class U> constexpr bool is_base_of_v =
            std::is_base_of<cu::remove_all_t<T>, cu::remove_all_t<U>>::value ||
            std::is_base_of<cu::remove_all_t<U>, cu::remove_all_t<T>>::value;

    template <class T, class U> constexpr bool is_related_v = is_base_of_v<T, U> || is_same_v<T, U>;

    template <class T> constexpr bool is_int = std::is_same_v<T, int>;

    template <class Class, class Value>
    using add_const = std::conditional_t<std::is_const_v<Class>, const Value, Value>;

    template <class  > struct __is_optional                   : std::false_type { };
    template <class T> struct __is_optional<std::optional<T>> : std::true_type { };
    template <class T> constexpr bool is_std_optional_v = __is_optional<remove_all_t<T>>::value;

    template <class  > struct __is_vector                 : std::false_type { };
    template <class T> struct __is_vector<std::vector<T>> : std::true_type  { };
    template <class T> constexpr bool is_std_vector_v = __is_vector<remove_all_t<T>>::value;

    template <class>            struct __is_map                 : std::false_type { };
    template <class T, class U> struct __is_map<std::map<T, U>> : std::true_type  { };
    template <class T> constexpr bool is_std_map_v = __is_map<remove_all_t<T>>::value;

    namespace _is_stl_container_impl{
        template <class T>                struct is_stl_container                       : std::false_type { };
        template <class T, std::size_t N> struct is_stl_container<std::array<T, N>>     : std::true_type { };
        template <class... Args>          struct is_stl_container<std::vector<Args...>> : std::true_type { };
        template <class... Args>          struct is_stl_container<std::list<Args...>>   : std::true_type { };
    }

    template <class T> struct is_stl_container {
        static constexpr bool value = _is_stl_container_impl::is_stl_container<std::decay_t<T>>::value;
    };

    template <class T>
    constexpr bool is_std_container_v = is_stl_container<T>::value;


    //MARK: - Pointer to member tools

    template<class T> struct pointer_to_member_class;
    template<class Class, class Value> struct pointer_to_member_class<Value Class::*> { using type = Class; };

    template <class T>
    using pointer_to_member_class_t = typename pointer_to_member_class<T>::type;

    template<class T> struct pointer_to_member_value;
    template<class Class, class Value> struct pointer_to_member_value<Value Class::*> { using type = Value; };

#ifdef __OBJC__
    template <class T> struct is_objc_object : std::integral_constant<bool, std::is_convertible_v<T, id> && !std::is_null_pointer_v<T>> { };
    template <class T> constexpr bool is_objc_object_v = is_objc_object<T>::value;
#else
    template <class T> constexpr bool is_objc_object_v = false;
#endif

    template <class T>
    struct pointer_to_member_info {

        using Class = typename pointer_to_member_class<T>::type;
        using Member = typename pointer_to_member_value<T>::type;

    private:

        template<class U> static auto invoke_result(U*) -> decltype((std::declval<Class>().*std::declval<U>())());
        template<class  > static auto invoke_result(...) -> void;

        static_assert(std::is_member_pointer_v<T>);

    public:

        static constexpr bool is_method = std::is_member_function_pointer_v<T>;

        using InvokeResult = decltype(pointer_to_member_info<T>::invoke_result<T>(nullptr));

        using Value = std::conditional_t<is_method, InvokeResult, Member>;

        static constexpr bool is_ref     = std::is_reference_v<Value>;
        static constexpr bool is_const   = std::is_const_v<std::remove_reference_t<Value>>;
        static constexpr bool is_pointer = std::is_pointer_v<Value>;
        
        static constexpr bool is_const_ref = std::is_pointer_v<Value>;

        static std::string to_string() {
            return std::string() + "\n" +
                   "is_ref: "     + (is_ref     ? "true" : "false") + "\n" +
                   "is_const: "   + (is_const   ? "true" : "false") + "\n" +
                   "is_pointer: " + (is_pointer ? "true" : "false");
        }

    };

    //MARK: - Tuple tools

    template <class     > struct is_tuple                   : std::false_type { };
    template <class ...T> struct is_tuple<std::tuple<T...>> : std::true_type  { };
    template <class T> constexpr bool is_tuple_v = is_tuple<remove_all_t<T>>::value;

    template <class T>
    using first_tuple_type = typename std::tuple_element_t<0, T>;

    template <int First, int Last, class Lambda>
    constexpr void static_for_range([[maybe_unused]] const Lambda& f) {
        if constexpr (First < Last) {
            f(std::integral_constant<int, First> { });
            static_for_range<First + 1, Last>(f);
        }
    }

    template <int Last, class Lambda>
    constexpr void static_for([[maybe_unused]] const Lambda& f) {
        static_for_range<0, Last>(f);
    }

    template <class Tuple, class Lambda>
    constexpr void iterate_tuple(const Tuple& tup, const Lambda& f) {
        static_assert(is_tuple_v<Tuple>);
        cu::static_for<std::tuple_size<Tuple>::value>([&](auto i) {
            f(std::get<i>(tup));
        });
    }

    template <class Tuple, class Lambda>
    constexpr void indexed_iterate_tuple(Tuple& tup, const Lambda& f) {
        static_assert(is_tuple_v<Tuple>);
        cu::static_for<std::tuple_size<Tuple>::value>([&](auto i) {
            f(i, std::get<i>(tup));
        });
    }

    template<class Class>
    class has_to_string {
        template<class T> static auto check(T*) -> std::is_same<decltype(std::declval<const T>().to_string()), std::string>;
        template<class  > static std::false_type check(...);
    public:
        static constexpr bool value = decltype(check<Class>(nullptr))::value;
    };

    template<class Class>
    inline constexpr bool has_to_string_v = has_to_string<Class>::value;

}

#define REVEAL_TEMPLATE(type) using __aaaa = typename type::____NoType;
