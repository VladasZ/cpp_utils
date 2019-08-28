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

        const std::string class_name = typeid(Class).name();
        const std::string member_name = typeid(Member).name();

        using Pointer = Member Class::*;
        const std::string name;
        const Pointer pointer;
        const Member default_value;
        Property(const std::string &name, Pointer pointer, const Member& def)
                :
                name(name), pointer(pointer), default_value(def) { }

        std::string to_string() const {
            return std::string() +
                   "Property: " + name + " of: " + class_name + " type: " + member_name;
        }

    };

    template<class Class, class Member, class Default>
    static const auto make_property(const std::string& name, Member Class::* pointer, const Default& def) {
        return Property<Class, Member>(name, pointer, def);
    }

}

#define PROPERTY(name, type, default_value) mapping::make_property(#name,  &type::name, default_value)
