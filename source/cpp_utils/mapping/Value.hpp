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

    private:

        void _check(Type type) const;

    };

}
