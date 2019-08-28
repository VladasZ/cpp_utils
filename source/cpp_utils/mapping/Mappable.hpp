//
//  Mappable.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 8/28/2019.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include <iostream>

#include "json.hpp"

#include "Property.hpp"
#include "IterateTuple.hpp"

namespace mapping {

    template<class T> class Mappable;

    template <class Type>
    static constexpr bool is_mappable = std::is_base_of<Mappable<Type>, Type>::value;

    template <class Type>
    using if_mappable = std::enable_if_t<is_mappable<Type>>;

    template<class T>
    class Mappable {

        using JSON = nlohmann::json;

        //Extraction

        template <class Member, class Property>
        static void extract(Member& member, const Property& property, const JSON& json) {
            member = json.value<Member>(property.name, property.default_value);
        }

        //Packing

        template <class Member, class Property>
        static void pack(const Member& member, const Property& property, JSON& json) {
            json[property.name] = member;
        }

        static T _parse(const JSON& json) {
            T object;
            cu::iterate_tuple(T::properties(), [&](auto property) {
                extract(object.*property.pointer, property, json);
            });
            return object;
        }

        template <class Object>
        static JSON _to_json(const Object& object) {
            nlohmann::json json;
            cu::iterate_tuple(T::properties(), [&](auto property) {
                pack(object.*property.pointer, property, json);
            });
            return json;
        }

    public:

        static T parse(const std::string& json) {
            return _parse(JSON::parse(json, nullptr, false));
        }

        template <class Object>
        static std::string to_json(const Object& object) {
            return _to_json(object).dump();
        }

        static void print_properties() {
            cu::iterate_tuple(T::properties(), [](auto property) {
                std::cout << property.to_string() << std::endl;
            });
        }
    };

}
