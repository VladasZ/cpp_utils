//
//  RangeConversion.cpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 03/02/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#include "Log.hpp"
#include "RangeConversion.hpp"

using namespace cu;

RangeConversion::RangeConversion(float minimum, float maximum, float converted_minimum, float converted_maximum)
: minimum(minimum), maximum(maximum), converted_minimum(converted_minimum), converted_maximum(converted_maximum) { }

float RangeConversion::convert(float value) {
    this->operator=(value);
    return _value;
}

void RangeConversion::operator=(float value) {

    auto value_range      = maximum - minimum;
    auto normalized_value = value - minimum;

    normalized_value /= value_range;

    auto converted_range = converted_maximum - converted_minimum;

    _value = converted_range * normalized_value;

    if (flip) {
        _value = converted_range - _value;
    }

    _value += converted_minimum;
}

RangeConversion::operator float() {
    return _value;
}
