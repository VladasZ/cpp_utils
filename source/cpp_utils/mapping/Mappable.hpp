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

    public:

        using This = T;

    private:

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

        JSON _to_json() const {
            nlohmann::json json;
            cu::iterate_tuple(T::properties(), [&](auto property) {
                pack(static_cast<const T*>(this)->*property.pointer, property, json);
            });
            return json;
        }

    public:

        static T parse(const std::string& json) {
            return _parse(JSON::parse(json, nullptr, false));
        }

        std::string to_json() const {
            return _to_json().dump();
        }

        static void print_properties() {
            cu::iterate_tuple(T::properties(), [](auto property) {
                std::cout << property.to_string() << std::endl;
            });
        }

        static std::string create_table_command() {
            std::string command = "CREATE TABLE IF NOT EXISTS ";

            command += T::class_name();
            command += " (\n";

            cu::iterate_tuple(T::properties(), [&](auto property) {
                command += property.name + " " + property.database_type_name() + ",\n";
            });

            command.pop_back();
            command.pop_back();

            command += "\n);";

            return command;
        }

        std::string insert_command() const {

            std::string columns;
            std::string values;

            cu::iterate_tuple(T::properties(), [&](auto property) {
                columns += property.name + ", ";

                auto value = static_cast<const T*>(this)->*property.pointer;

                if constexpr (property.is_string) {
                    values += std::string() + "\'" + value + "\',";
                }
                else {
                    values += std::to_string(value) + ",";
                }
            });

            columns.pop_back();
            columns.pop_back();

            values.pop_back();

            return std::string() +
            "INSERT INTO " + T::class_name() + " (" + columns + ")\n" +
            "VALUES(" + values + ");";
        }
    };

}
