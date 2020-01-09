//
//  Property.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 8/28/2019.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include <string>

namespace mapping {

    enum class PropertyType {
        None,
        Secure,
        Unique
    };

    template<
            class _Class,
            class _Member,
            PropertyType type = PropertyType::None
    >
    class Property {
    public:

        using Class = _Class;
        using Member = std::remove_const_t<_Member>;

        using Pointer = _Member Class::*;

        constexpr static bool is_string  = std::is_same_v<Member, std::string>;
        constexpr static bool is_float   = std::is_floating_point_v<float>;
        constexpr static bool is_integer = std::numeric_limits<Member>::is_integer;

        constexpr static bool is_secure  = type == PropertyType::Secure;
        constexpr static bool is_unique  = type == PropertyType::Unique;

        static_assert(is_string || is_float || is_integer, "Invalid property type");

        const std::string_view class_name = Class::class_name();
        const std::string_view member_name = database_type_name();

        const std::string_view name;
        const Pointer pointer;

        constexpr Property(const std::string_view& name, Pointer pointer) :
                name(name), pointer(pointer) {
        }

        constexpr std::string_view database_type_name() const {
            if constexpr (is_string) {
                return "TEXT";
            }
            else if constexpr (is_float) {
                return "REAL";
            }
            else if constexpr (is_integer) {
                return "INTEGER";
            }
            else {
#ifdef MICROCONTROLLER_BUILD
                Fatal("Invalid member type");
#else
                Fatal(std::string() + "Invalid member type: " + typeid(Member).name());
#endif
            }
        }

        std::string to_string() const {
            return std::string() +
                   "Property: " + std::string(name) + " of: " + std::string(class_name) + " type: " + std::string(member_name);
        }

    };

    template <class                           > struct is_property                    : std::false_type { };
    template <class C, class M, PropertyType t> struct is_property<Property<C, M, t>> : std::true_type  { };

}
