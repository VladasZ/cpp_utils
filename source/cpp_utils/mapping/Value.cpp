//
// Created by Vladas Zakrevskis on 03/09/2019.
//

#include <map>
#include <stdexcept>

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

	if (!_string_is_valid(str)) {
		throw std::runtime_error("Invalid symbol in string value. Valid symbols are: [A-Za-z0-9.@]");
	}

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

bool Value::operator==(const Value& other) const {
    return _data == other._data;
}

bool Value::operator!=(const Value& other) const {
    return _data != other._data;
}

std::string Value::database_string() const {
    if (_type == String) {
        return "\'" + _data + "\'";
    }
    return _data;
}

std::string Value::to_string() const {
    return _data;
}

void Value::_check(Value::Type type) const {

    if (type == _type)
        return;

    throw std::runtime_error(
        "Invalid mapping::Value conversion. Expected: " + type_to_string[_type] +
        " got: " + type_to_string[type]);
}

bool Value::_string_is_valid(const std::string& string) const {
	for (auto symbol : string) {
		if (
			(symbol >= 'A' && symbol <= 'Z') ||
			(symbol >= 'a' && symbol <= 'z') ||
			(symbol >= '0' && symbol <= '9') ||
			(symbol == ' ') ||
			(symbol == '@') ||
			(symbol == '.')
			)
		{
			continue;
		}
		else {
			return false;
		}
	}
	return true;
}

