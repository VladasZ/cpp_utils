//
//  Array.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 6/07/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#include <memory>
#include <vector>
#include <iostream>
#include <functional>
#include <type_traits>


#include "System.hpp"
#include "MetaHelpers.hpp"

namespace cu::array {

    template <class Array>
    static size_t bytes_size(const Array& array) {
        return sizeof(typename Array::value_type) * array.size();
    }

    template <class Type, class Array>
    static size_t size_in(const Array& array) {
        return bytes_size(array) / sizeof(Type);
    }

    template <class Array, class Value = typename Array::value_type, class Predicate = std::function<bool(Value, Value)>>
    static auto find(const Array& array, Predicate predicate) {
        auto val = std::numeric_limits<Value>::min();
        for (auto value : array) {
            if (predicate(value, val)) {
                val = value;
            }
        }
        return val;
    }

    template <class Array>
    static auto max(const Array& array) {
        return find(array, [](auto a, auto b) { return a > b; });
    }

    template <class Array>
    static auto min(const Array& array) {
        return find(array, [](auto a, auto b) { return a < b; });
    }

    template <class Array>
    static void print(const Array& array) {
        for(const auto& val : array) {
            std::cout << val.to_string() << std::endl;
        }
    }

    template <class Array>
    static constexpr auto static_size = std::tuple_size<Array>::value;

    template <class TargetArray, class Array>
    static auto convert(const Array& array) {
        using ArrayValue = typename Array::value_type;
        using TargetValue = typename TargetArray::value_type;

        const auto target_array_size = array.size() * (sizeof(ArrayValue) / sizeof(TargetValue));
        auto data = reinterpret_cast<const TargetValue*>(array.data());
        return TargetArray { data, data + target_array_size };
    }

    template <class Array, class Value = typename Array::value_type>
    static void remove(Array& array, const Value& value) {
        auto position = std::find(array.begin(), array.end(), value);
        if (position != array.end()) {
            array.erase(position);
        }
    }

    template <class Array, class ArrayToRemove,
            std::enable_if_t<std::is_same_v<typename Array::value_type, typename ArrayToRemove::value_type>> = 0>
    static void remove(Array& array, const ArrayToRemove& objects_to_remove) {
        for (auto object : objects_to_remove) {
            remove(array, object);
        }
    }

    template <class Array, class Value = typename Array::value_type, class Predicate = std::function<bool(const Value&)>>
    static void remove_where(Array& array, Predicate predicate) {
        for (auto object : array) {
            if (predicate(object)) {
                remove(array, object);
            }
        }
    }

    template <class Array, class Value = typename Array::value_type>
    static bool contains(const Array& array, const Value& value) {
        return std::find(array.begin(), array.end(), value) != array.end();
    }

    template <class T>
    class backwards {
        T& _arr;
    public:
        backwards(T &arr) : _arr(arr) { }
        auto begin() { return _arr.rbegin(); }
        auto end() { return _arr.rend(); }
    };

    template <auto& array,
            class Array = cu::remove_all_t<decltype(array)>,
            class Value = typename Array::value_type>
    constexpr static bool static_exists(const Value& value) {
        bool result = false;
        static_for<0, array.size()>([&] (const auto& index) {
            if (value == array[index.value]) {
                result = true;
            }
        });
        return result;
    }

}

