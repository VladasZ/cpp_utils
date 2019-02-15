//
//  Result.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 2/15/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

template <class T>
class Result {
public:
    const float error = 0;
    T result;
    Result(float error, const T& result) : error(error), result(result) { }
};


