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
        erase(std::remove_if(this->begin(), this->end(),  predicate, this->end()));
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

template <class T>
[[maybe_unused]]
static size_t bytes_size(const T& array) {
    return sizeof(typename T::value_type) * array.size();
}

}
