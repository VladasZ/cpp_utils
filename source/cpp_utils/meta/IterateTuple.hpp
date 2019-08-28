//
//  IterateTuple.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 8/28/2019.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include <type_traits>

namespace cu {

    template<typename Tuple, typename F, std::size_t ...Indices>
    void __for_each_impl(Tuple&& tuple, F&& f, std::index_sequence<Indices...>) {
        using swallow = int[];
        (void) swallow{1, (f(std::get<Indices>(std::forward<Tuple>(tuple))), void(), int{})...};
    }

    template<typename Tuple, typename F>
    void iterate_tuple(Tuple&& tuple, F&& f) {
        constexpr std::size_t N = std::tuple_size_v<std::remove_reference_t<Tuple>>;
        __for_each_impl(std::forward<Tuple>(tuple), std::forward<F>(f), std::make_index_sequence<N>{});
    }

}