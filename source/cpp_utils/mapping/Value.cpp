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
	Value::check_string(str);
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

bool Value::is_empty() const {
	if (_type == String) {
		return _data.empty();
	}
	else if (_type == Int) {
		return this->operator int() == 0;
	}
	else if (_type == Float) {
		return this->operator float() == 0.0f;
	}
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

void Value::check_string(const std::string& string) {
	for (auto symbol : string) {
		if (
			(symbol >= 'A' && symbol <= 'Z') ||
			(symbol >= 'a' && symbol <= 'z') ||
			(symbol >= '0' && symbol <= '9') ||
			(symbol == ' ') ||
			(symbol == '-') ||
			(symbol == '@') ||
			(symbol == '.')
			)
		{
			continue;
		}
		else {
			throw std::runtime_error("Invalid symbol in string value. Valid symbols are: [A-Za-z0-9.@]");
		}
	}
}
