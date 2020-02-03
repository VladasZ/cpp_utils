//
//  Property.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 03/02/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#include <functional>

namespace cu {

    template <class T>
    class Property {
    public:

        using Getter = std::function<T&()>;
        using DidSet = std::function<void()>;

        T& reference;
        DidSet did_set;

        Property(T& reference) : reference(reference) { }

        void operator = (T new_value) {
            reference = new_value;
            did_set();
        }

        void operator = (std::function<void(T&)> edit) {
            edit(reference);
            did_set();
        }

        operator T() {
            return reference;
        }

        T operator()() {
            return reference;
        }

        void reset() {
            reference = T { };
        }

    };

}
