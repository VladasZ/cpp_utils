//
//  JSONMappable.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 9/13/2019.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include <iostream>

#include "json.hpp"

#include "Mappable.hpp"

namespace mapping {

    using JSON = nlohmann::json;

    template<class T> class JSONMappable;

    template <class Type>
    static constexpr bool is_json_mappable = std::is_base_of<JSONMappable<Type>, Type>::value;

    template<class T>
    class JSONMappable : public virtual Mappable<T> {

    private:

        template <class Member, class Property>
        static void _extract(Member& member, const Property& property, const JSON& json) {
            member = json.value<Member>(property.name, Member { });
        }

        template <class Member, class Property>
        static void _pack(const Member& member, const Property& property, JSON& json) {
            json[property.name] = member;
        }

        JSON _to_json() const {
            JSON json;
            T::iterate_properties([&](auto property) {
                _pack(this->template _value(property), property, json);
            });
            return json;
        }

        static T _parse_json(const JSON& json) {
            T object;
            T::iterate_properties([&](auto property) {
                _extract(object.*property.pointer, property, json);
            });
            return object;
        }

        static T _parse_string(const std::string& json) {
            return parse(JSON::parse(json, nullptr, false));
        }

    public:

        template<class JSONType>
        static T parse(const JSONType& json) {
            if constexpr (std::is_same_v<JSONType, JSON>) {
                return _parse_json(json);
            }
            else {
                return _parse_string(json);
            }
        }

        std::string to_json() const {
            return _to_json().dump();
        }

        template<class Array>
        static std::string array_to_json(const Array& array) {
            static_assert(std::is_same_v<typename Array::value_type, T>);
            auto result = JSON::array();
            for (auto value : array)
                result.push_back(value._to_json());
            return result.dump();
        }

    };

}
