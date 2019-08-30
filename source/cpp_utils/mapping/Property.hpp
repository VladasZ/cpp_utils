//
//  Property.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 8/28/2019.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include <iostream>

namespace mapping {

    template<class Class, class Member>
    class Property {
    public:

        using Pointer = Member Class::*;

        constexpr static bool is_string  = std::is_same_v<Member, std::string>;
        constexpr static bool is_float   = std::is_floating_point_v<Member>;
        constexpr static bool is_integer = std::is_integral_v<Member>;

        const std::string class_name  = typeid(Class).name();
        const std::string member_name = typeid(Member).name();

        const std::string name;
        const Pointer pointer;

        constexpr Property(const std::string& name, Pointer pointer) :
                name(name), pointer(pointer) {
            static_assert(is_string || is_float || is_integer, "Invalid property type");
        }

        std::string database_type_name() const {
            if constexpr (is_string) {
                return "TEXT";
            }
            else if (is_float) {
                return "REAL";
            }
            else if (is_integer) {
                return "INTEGER";
            }
            else {
                throw std::string() + "Invalid member type: " + typeid(Member).name();
            }
        }

        std::string to_string() const {
            return std::string() +
                   "Property: " + name + " of: " + class_name + " type: " + member_name;
        }

    };

    template<class Class, class Member>
    static const auto make_property(const std::string& name, Member Class::* pointer) {
        return Property<Class, Member>(name, pointer);
    }

}

#define PROPERTY(name) mapping::make_property(#name,  &This::name)
