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
				return std::string() + "\'" + this->_value(property) + "\'";
			}
            else {
				return std::to_string(this->_value(property));
			}
        }

    public:

		static const inline std::string sqlite_id_key = "rowid";

        static std::string create_table_command() {
            std::string command = "CREATE TABLE IF NOT EXISTS ";

            command += T::class_name();
            command += " (\n";

            T::iterate_properties([&](auto property) {
                command += property.name + " " + property.database_type_name();
                if (property.is_unique) {
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
            return command + " WHERE " + sqlite_id_key + " = " + std::to_string(this->id) + ";";
        }

        std::string select_command_with_id() const {
            return SQLiteMappable<T>::select_command_with_key_value(sqlite_id_key, this->id);
        }

		std::string select_command_with_unique_value() const {
			return SQLiteMappable<T>::select_command_with_key_value(this->unique_key, this->unique_value());
		}

		static std::string static_select_command_with_id(ID id) {
            return select_command_with_key_value(sqlite_id_key, id);
        }

		static std::string select_command_with_key_value(std::string key, Value value) {
			return "SELECT rowid, * FROM " + T::class_name() +
				  " WHERE " + key + " = " + value.database_string() + ";";
		}

        std::string select_where_command() const {
			auto field = this->edited_field();
			auto value = this->_TEMPLATE get<Value>(field);
			return select_command_with_key_value(field, value);
        }

		std::string delete_command() const {
			return T::delete_command_with_primary_value(this->primary_value());
		}

		static std::string delete_command_with_primary_value(const Value& value) {
			return "DELETE FROM " + T::class_name() + " WHERE " + T::primary_key + " = " + value.database_string() + ";";
		}

        static std::string select_all_command() {
            return "SELECT rowid, * FROM " + T::class_name() + ";";
        }

    };
}
