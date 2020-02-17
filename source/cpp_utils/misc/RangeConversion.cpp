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

float RangeConversion::convert(float value) const {
    auto value_range      = maximum - minimum;
    auto normalized_value = value - minimum;

    normalized_value /= value_range;

    auto converted_range = converted_maximum - converted_minimum;

    auto result = converted_range * normalized_value;

    if (flip) {
        result = converted_range - result;
    }

    return result + converted_minimum;
}
