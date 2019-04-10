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

#include "System.hpp"

namespace cu::array {

template <class Array>
[[maybe_unused]]
static size_t bytes_size(const Array& array) {
    return sizeof(typename Array::value_type) * array.size();
}

template <class Type, class Array>
[[maybe_unused]]
static size_t size_in(const Array& array) {
    return bytes_size(array) / sizeof(Type);
}

template <class Array, class Type = typename Array::value_type, class Predicate = std::function<bool(Type, Type)>>
[[maybe_unused]]
static auto find(const Array& array, Predicate predicate) {
    auto val = std::numeric_limits<Type>::min();
    for (auto value : array) {
        if (predicate(value, val))
            val = value;
    }
    return val;
}

template <class Array>
[[maybe_unused]]
static auto max(const Array& array) {
    return find(array, [](auto a, auto b) { return a > b; });
}

template <class Array>
[[maybe_unused]]
static auto min(const Array& array) {
    return find(array, [](auto a, auto b) { return a < b; });
}

template <class Array>
[[maybe_unused]]
static void print(const Array& array) {
    for(const auto& val : array)
        std::cout << val.to_string() << std::endl;
}

template <class Array>
static constexpr auto static_size = std::tuple_size<Array>::value;

}
