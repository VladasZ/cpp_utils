//
//  STDExperimental.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 01/08/2020.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#ifdef EXPERIMENTAL_OPTIONAL
#include <experimental/optional>
namespace std {
    template<class T>
    using optional = std::experimental::optional<T>;
}
#else
#include <optional>
#endif
