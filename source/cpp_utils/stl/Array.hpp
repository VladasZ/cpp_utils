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
#include <functional>

#include "System.hpp"

template <class T>
class Array : public std::vector<T> {
    using __array = std::vector<T>;
public:
    using __array::__array;

    using Ptr       = std::shared_ptr<T>;
    using Predicate = std::function<bool(const T&)>;

    Array(const std::vector<T>& vector) {
        for (const auto& obj : vector)
            this->push_back(obj);
    }

    auto index_of(const T& object) {
        return std::find(this->begin(), this->end(), object);
    }

    void remove(const T& object) {
        auto iter = std::find(this->begin(), this->end(), object);
        if (iter == this->end())
            return;
        this->erase(iter);
    }

    void remove_if(const Predicate& predicate) {
        erase(std::remove_if(this->begin(), this->end(), predicate, this->end()));
    }

    template <class ...Args>
    void append(Args ...args) {
        this->insert(this->end(), std::initializer_list<T> { args... });
    }

    void insert_at(size_t index, const T& object) {
        this->emplace(this->begin() + index, object);
    }

    T random() const {
        return this->at(System::random(static_cast<int>(this->size())));
    }
    
    size_t bytes_size() const {
        return sizeof(T) * this->size();
    }
};

namespace array {

template <class ArrayType>
[[maybe_unused]]
static size_t bytes_size(const ArrayType& array) {
    return sizeof(typename ArrayType::value_type) * array.size();
}

template <class Type, class ArrayType>
[[maybe_unused]]
static size_t size_in(const ArrayType& array) {
    return bytes_size(array) / sizeof(Type);
}

template <class ArrayType, class Type = typename ArrayType::value_type, class Predicate = std::function<bool(Type, Type)>>
[[maybe_unused]]
static auto max(const ArrayType& array, Predicate predicate = [](auto a, auto b) { return a > b; }) {
    auto max = std::numeric_limits<Type>::min();
    for (auto value : array) {
        if (predicate(value, max))
            max = value;
    }
    return max;
}

template <class ArrayType, class Type = typename ArrayType::value_type, class Predicate = std::function<bool(Type, Type)>>
[[maybe_unused]]
static auto min(const ArrayType& array, Predicate predicate = [](auto a, auto b) { return a < b; }) {
    auto min = std::numeric_limits<Type>::max();
    for (auto value : array) {
        if (predicate(value, min))
            min = value;
    }
    return min;
}

}
