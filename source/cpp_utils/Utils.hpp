//
//  Utils.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 7/1/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include <string>
#include <functional>
#include <type_traits>

namespace cu {

using Callback = std::function<void()>;

template <class T>
using ArrayType = decltype(std::declval<T>()[0]);

#ifndef MICROCONTROLLER_BUILD
template <class T>
const std::string type_name = typeid(T).name();
#endif

template <class T>
void increment_with_limit(T& value, size_t limit = 10) {
    value++;
    if (value == limit)
        value = 0;
}

template <class T>
constexpr bool is_string =
        std::is_same_v<ArrayType<T>, char> ||
        std::is_same_v<T, const char*> ||
        std::is_same_v<T, std::string>;

}
