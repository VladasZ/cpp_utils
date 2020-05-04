//
//  ArrayView.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 03/05/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#include <stdlib.h>


namespace cu {

    template<class T>
    class ArrayView {

    private:

        const size_t _size;
        const T* const _data;

    public:

        explicit ArrayView() : _size(0), _data(nullptr) { }

        template<template<class> class Container>
        ArrayView(const Container<T>& container) : _size(container.size()), _data(container.data()) { }

        bool empty() const { return _size == 0; }
        size_t size() const { return _size; }

        const T* data() const { return _data; }
        const T* begin() const { return _data; }
        const T* end() const { return _data + _size; }

        const T& operator[](int i) const { return _data[i]; }

    };

}
