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

        size_t _size = 0;
        T *_data = nullptr;

    public:

        explicit ArrayView() = default;

        explicit ArrayView(size_t size, const T *data) : _size(size), _data(data) {}

        template<class Container>
        explicit ArrayView(const Container &container) {
            _size = container.size();
            _data = container.data();
        }

        size_t size() const { return _size; }

        const T *data() const { return _data; }

        const T &operator[](int i) const {
            return _data[i];
        }

    };

}
