//
//  RangeConversion.cpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 03/02/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#include "Log.hpp"
#include "GmMath.hpp"
#include "RangeConversion.hpp"

using namespace cu;

RangeConversion::RangeConversion(float begin, float end, float converted_begin, float converted_end)
: begin(begin), end(end), converted_begin(converted_begin), converted_end(converted_end) { }

float RangeConversion::convert(float value) {
    this->operator=(value);
    return _value;
}

void RangeConversion::operator=(float value) {

    auto value_range      = end    - begin;
    auto normalized_value = value - begin;

    normalized_value /= value_range;

    auto converted_range = converted_end - converted_begin;

    _value = converted_range * normalized_value;

    if (flip) {
        _value = converted_range - _value;
    }

    _value += converted_begin;
}

RangeConversion::operator float() {
    return _value;
}
