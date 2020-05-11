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

#include "Log.hpp"
#include "System.hpp"
#include "MetaHelpers.hpp"


namespace cu::array {

    template <class Array>
    constexpr static size_t bytes_size(const Array& array) {
        return sizeof(typename Array::value_type) * array.size();
    }

    template <class Type, class Array>
    constexpr static size_t size_in(const Array& array) {
        return bytes_size(array) / sizeof(Type);
    }

    template <class Array>
    static std::string to_string(const Array& array) {
        if (array.empty()) return "[]";
        std::string result = "[";
        for (auto& val : array) {
            result += cu::Log::to_string((int)val) + " ";
        }
        result.pop_back();
        return result + "]";
    }

    template <class Array>
    static void print(const Array& array) {
        for (const auto& val : array) {
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
        if (position == array.end()) return;
        array.erase(position);
    }

    template <class Array, class ArrayToRemove>
    static void remove_from(Array& array, const ArrayToRemove& objects_to_remove) {
        for (const auto& object : objects_to_remove) {
            remove(array, object);
        }
    }

    template <class Array, class Value = typename Array::value_type, class Predicate = std::function<bool(const Value&)>>
    static void  remove_where(Array& array, Predicate predicate) {
        auto position = std::find_if(array.begin(), array.end(), predicate);
        if (position != array.end()) {
            array.erase(position);
        }
    }

    template <class Array, class Value = typename Array::value_type>
    constexpr static bool contains(const Array& array, const Value& value) {
        return std::find(array.begin(), array.end(), value) != array.end();
    }

    template <class T>
    class backwards {
        T& _arr;
    public:
        explicit backwards(T &arr) : _arr(arr) { }
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

    template <class A, class B>
    constexpr static void append(A& a, const B& b) {
        a.insert(std::end(a), std::begin(b), std::end(b));
    }

}

