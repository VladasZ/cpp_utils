//
//  Array.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 6/07/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <functional>
#include <type_traits>


namespace cu::container {

    template <class Array>
    constexpr size_t bytes_size(const Array& array) {
        return sizeof(typename Array::value_type) * array.size();
    }

    template <class Type, class Array>
    constexpr size_t size_in(const Array& array) {
        return bytes_size(array) / sizeof(Type);
    }

    template <class Array>
    std::string to_string(const Array& array) {
        if (array.empty()) return "[]";
        std::string result = "[";
        for (auto& val : array) {
            result += std::to_string(static_cast<int>(val)) + " ";
        }
        result.pop_back();
        return result + "]";
    }

    template <class Array>
    void print(const Array& array) {
        for (const auto& val : array) {
            std::cout << val.to_string() << std::endl;
        }
    }

    template <class Array, class Value = typename Array::value_type>
    void remove(Array& array, const Value& value) {
        auto position = std::find(array.begin(), array.end(), value);
        if (position == array.end()) return;
        array.erase(position);
    }

    template <class Array, class ArrayToRemove>
    void remove_from(Array& array, const ArrayToRemove& objects_to_remove) {
        for (const auto& object : objects_to_remove) {
            remove(array, object);
        }
    }

    template <class Array, class Value = typename Array::value_type, class Predicate = std::function<bool(const Value&)>>
    void remove_where(Array& array, Predicate predicate) {
        auto position = std::find_if(array.begin(), array.end(), predicate);
        if (position != array.end()) {
            array.erase(position);
        }
    }

    template <class Array, class Value = typename Array::value_type, class Predicate = std::function<bool(const Value&)>>
    const Value& where(Array& array, Predicate predicate) {
        return *std::find_if(array.begin(), array.end(), predicate);
    }

    template <class Array, class Value = typename Array::value_type>
    constexpr bool contains(const Array& array, const Value& value) {
        return std::find(array.begin(), array.end(), value) != array.end();
    }

    template <class T>
    class backwards {
        T& _arr;
    public:
        explicit backwards(T &arr) : _arr(arr) { }
        auto begin() const { return _arr.rbegin(); }
        auto end() const { return _arr.rend(); }
    };

    template <class A, class B>
    constexpr void append(A& a, const B& b) {
        a.insert(std::end(a), std::begin(b), std::end(b));
    }

    template <class Array, class Transform>
    constexpr auto transform(const Array& array, const Transform& transform) {
        using Value = typename Array::value_type;
        using TransformedValue = typename std::result_of<Transform>::type;
        std::vector<TransformedValue> result;
        std::transform(array.begin(), array.end(), array.result(), transform);
        return result;
    }

	template <class Array>
	constexpr auto summ(const Array& array) {
		return std::accumulate(array.begin(), array.end(), 0.0f);
	}

}

