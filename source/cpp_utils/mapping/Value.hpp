//
// Created by Vladas Zakrevskis on 03/09/2019.
//


#pragma once

#include <map>
#include <string>

namespace mapping {

    class Value {

        enum Type {
            String,
            Int,
            Float,
            NotInitialized
        };

        static std::map<Type, std::string> type_to_string;

    private:

        Type _type = NotInitialized;
        std::string _data;

    public:

        Value() = default;
        Value(const std::string&);
        Value(int);
        Value(float);

        operator std::string() const;
        operator int() const;
        operator float() const;

        template<class T>
        T convert() const {
            if constexpr (std::is_same_v<T, int>) {
                _check(Int);
                return this->operator float();
            }
            else if constexpr (std::is_same_v<T, float>) {
                _check(Float);
                return this->operator int();
            }
            else if constexpr (std::is_same_v<T, std::string>) {
                _check(String);
                return this->operator std::string();
            }
        }

        bool operator == (const Value&) const;
        bool operator != (const Value&) const;

        std::string database_string() const;

        std::string to_string() const;

		static void check_string(const std::string&);

    private:
        void _check(Type) const;

    };

}
