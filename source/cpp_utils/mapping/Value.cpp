//
// Created by Vladas Zakrevskis on 03/09/2019.
//

#include <map>

#include "Value.hpp"

using namespace std;
using namespace mapping;

map<Value::Type, string> Value::type_to_string = {
        { Value::Type::String,         "String"         },
        { Value::Type::Int,            "Int"            },
        { Value::Type::Float,          "Float"          },
        { Value::Type::NotInitialized, "NotInitialized" },
};

Value::Value(const std::string& str) : _type(String), _data(str) {

}

Value::Value(int i) : _type(Int), _data(std::to_string(i)) {

}

Value::Value(float f) : _type(Float), _data(std::to_string(f)) {

}

Value::operator std::string() const {
    _check(String);
    return _data;
}

Value::operator int() const {
    _check(Int);
    return std::stoi(_data);
}

Value::operator float() const {
    _check(Float);
    return std::stof(_data);
}

std::string Value::to_string() const {
    return _data;
}

void Value::_check(Value::Type type) const {

    if (type == _type)
        return;

    throw std::string() +
        "Invalid mapping::Value conversion. Expected: " + type_to_string[_type] +
        " got: " + type_to_string[type];
}
