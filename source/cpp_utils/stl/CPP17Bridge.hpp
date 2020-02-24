//
//  CPP17Bridge.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 24/02/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#if __cplusplus < 201703L
#define NO_CPP_17_BUILD
#else
#define CPP_17_BUILD
#endif

#ifdef NO_CPP_17_BUILD

#include <type_traits>

namespace std {

    template <class T> using remove_pointer_t   = typename remove_pointer<T>::type;
    template <class T> using remove_reference_t = typename remove_reference<T>::type;
    template <class T> using remove_cv_t        = typename remove_cv<T>::type;

    template <std::size_t I, class T>
    using tuple_element_t = typename std::tuple_element<I, T>::type;

}

#endif
