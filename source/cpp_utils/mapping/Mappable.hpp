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

#include "Value.hpp"
#include "Property.hpp"
#include "IterateTuple.hpp"

namespace mapping {

    using JSON = nlohmann::json;

    template<class T> class Mappable;

    template <class Type>
    static constexpr bool is_mappable = std::is_base_of<Mappable<Type>, Type>::value;

    template <class Type>
    using if_mappable = std::enable_if_t<is_mappable<Type>>;

    template<class Type>
    static constexpr bool supported =
            std::is_same_v<Type, std::string> ||
            std::is_same_v<Type, int        > ||
            std::is_same_v<Type, float      >;

    template<class T>
    class Mappable {

    public:

        using This = T;

    private:

        //Extraction

        template <class Member, class Property>
        static void extract(Member& member, const Property& property, const JSON& json) {
            member = json.value<Member>(property.name, Member { });
        }

        //Packing

        template <class Member, class Property>
        static void pack(const Member& member, const Property& property, JSON& json) {
            json[property.name] = member;
        }


        JSON _to_json() const {
            JSON json;
            T::iterate_properties([&](auto property) {
                pack(_value(property), property, json);
            });
            return json;
        }

        static T _parse_json(const JSON& json) {
            T object;
            T::iterate_properties([&](auto property) {
                extract(object.*property.pointer, property, json);
            });
            return object;
        }

        static T _parse_string(const std::string& json) {
            return parse(JSON::parse(json, nullptr, false));
        }

        template<class Prop>
        auto _value(const Prop& property) const {
            return static_cast<const T*>(this)->*property.pointer;
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

        static void print_properties() {
            T::iterate_properties([](auto property) {
                std::cout << property.to_string() << std::endl;
            });
        }

        template<class Array>
        static std::string array_to_json(const Array& array) {
            static_assert(std::is_same_v<typename Array::value_type, T>);
            auto result = JSON::array();
            for (auto value : array)
                result.push_back(value._to_json());
            return result.dump();
        }

        template<class Closure>
        static void iterate_properties(Closure&& closure) {
            cu::iterate_tuple(T::properties(), closure);
        }

        //SQLITE

        static std::string create_table_command() {
            std::string command = "CREATE TABLE IF NOT EXISTS ";

            command += T::class_name();
            command += " (\n";

            T::iterate_properties([&](auto property) {
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

            T::iterate_properties([&](auto property) {
                columns += property.name + ", ";

                auto value = _value(property);

                if constexpr (property.is_string)
                    values += std::string() + "\'" + value + "\',";
                else
                    values += std::to_string(value) + ",";
            });

            columns.pop_back();
            columns.pop_back();

            values.pop_back();

            return std::string() +
                   "INSERT INTO " + T::class_name() + " (" + columns + ")\n" +
                   "VALUES(" + values + ");";
        }

        std::string select_where_command() const {
            auto field = edited_field();
            auto value = get<Value>(field).database_string();
            return "SELECT * FROM " + T::class_name() +
            " WHERE " + field + " = " + value + ";";
        }

        static std::string select_command() {
            return "SELECT * FROM " + T::class_name() + ";";
        }

        static T empty() {
            T result;
            T::iterate_properties([&](auto property) {
                result.*property.pointer = typename decltype(property)::Member { };
            });
            return result;
        }

        std::string edited_field() const {
            std::string result;
            bool found = false;
            T::iterate_properties([&](auto property) {
                if (found) {
                    return;
                }
                if (_value(property) != typename decltype(property)::Member { }) {
                    result = property.name;
                    found = true;
                }
            });
            if (!found) {
                throw std::runtime_error("No edited field found in class " + T::class_name());
            }
            return result;
        }

        template<class Field>
        Field get(const std::string& name) const {
            static_assert(supported<Field> || std::is_same_v<Field, Value>,
                    "Type is not supported");

            if (name.empty()) {
                throw std::runtime_error("Field get::No property name for class " + T::class_name());
            }

            Value result;
            bool found = false;
            T::iterate_properties([&](auto property) {
                if (found) return;
                if (property.name == name) {
                    found = true;
                    result = _value(property);
                }
            });

            if (!found) {
                throw std::runtime_error("Field get::No property: " + name + " in class " + T::class_name());
            }

            return result;
        }
    };

}
