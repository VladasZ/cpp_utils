//
//  SQLiteMappable.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 9/13/2019.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include "Mappable.hpp"

namespace mapping {

    template<class T> class SQLiteMappable;

    template <class Type>
    static constexpr bool is_sqlite_mappable = std::is_base_of<SQLiteMappable<Type>, Type>::value;

    template<class T>
    class SQLiteMappable : public virtual Mappable<T> {

        template<class Prop>
        std::string _database_value(const Prop& property) const {
            if constexpr (Prop::is_string) {
				//return std::string() + "\'" + this->template _value(property) + "\'";
				return std::string() + "\'" + this->_value(property) + "\'";
			}
            else {
				//return std::to_string(this->template _value(property));
				return std::to_string(this->_value(property));
			}
        }

    public:

        static std::string create_table_command() {
            std::string command = "CREATE TABLE IF NOT EXISTS ";

            command += T::class_name();
            command += " (\n";

            T::iterate_properties([&](auto property) {
                command += property.name + " " + property.database_type_name();
                if (property.is_primary) {
                    command += " UNIQUE";
                }
                command += ",\n";
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
                values += _database_value(property) + ",";
            });

            columns.pop_back();
            columns.pop_back();

            values.pop_back();

            return std::string() +
                   "INSERT INTO " + T::class_name() + " (" + columns + ")\n" +
                   "VALUES(" + values + ");";
        }

        std::string update_command() const {
            std::string command = "UPDATE " + T::class_name() + " SET ";
            T::iterate_properties([&](auto property) {
                command += property.name + " = " + _database_value(property) + ", ";
            });
            command.pop_back();
            command.pop_back();
            return command + " WHERE " + T::primary_key + " = " + this->primary_value().database_string() + ";";
        }

        std::string select_command() const {
            auto primary_value = this->primary_value().database_string();
            return "SELECT * FROM " + T::class_name() +
                   " WHERE " + T::primary_key + " = " + primary_value + ";";
        }

        std::string select_where_command() const {
			//auto field = this->template edited_field();
			auto field = this->edited_field();
			//auto value = this->template get<Value>(field).database_string();
			auto value = this->get<Value>(field).database_string();
			return "SELECT * FROM " + T::class_name() +
                   " WHERE " + field + " = " + value + ";";
        }

        static std::string select_all_command() {
            return "SELECT * FROM " + T::class_name() + ";";
        }

    };
}
