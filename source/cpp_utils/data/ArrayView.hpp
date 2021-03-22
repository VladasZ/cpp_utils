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

        const T* const _data;
        const size_t _size;

    public:

        ArrayView() : _data(nullptr), _size(0) { }

        explicit ArrayView(const T* data, size_t size) : _data(data), _size(size) { }

        template<class Container, class Value = typename Container::value_type>
        constexpr ArrayView(const Container& container)
        : _data(reinterpret_cast<const T*>(container.data())),
          _size(container.size() * (sizeof(Value) / sizeof(T))) { }

        bool empty()  const { return _size == 0; }
        size_t size() const { return _size; }

        const T* data()  const { return _data; }
        const T* begin() const { return _data; }
        const T* end()   const { return _data + _size; }

        const T& operator[](int i) const { return _data[i]; }

    };

}
