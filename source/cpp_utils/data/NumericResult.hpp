//
//  NumericResult.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 2/15/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include <limits>

template <class T>
class NumericResult {
    using This = NumericResult<T>;
    static inline float min_error = std::numeric_limits<float>::max();
public:
    const bool has_minimal_error;
    const float error = 0;
    T result;
    NumericResult(float error, const T& result)
    : error(error), result(result), has_minimal_error(error < This::min_error) {
        if (has_minimal_error)
            This::min_error = error;
    }
};
