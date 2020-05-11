//
//  RangeConversion.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 07/05/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#include "RangeConversion.hpp"

using namespace cu;


float RangeConversion::min() const {
    return _min;
}

float RangeConversion::max() const {
    return _max;
}

void RangeConversion::set_min(float min) {
    _min = min;
    _update_range();
}

void RangeConversion::set_max(float max) {
    _max = max;
    _update_range();
}

void RangeConversion::set_target_min(float min) {
    _target_min = min;
    _update_converted_range();
}

void RangeConversion::set_target_max(float max) {
    _target_max = max;
    _update_converted_range();
}

void RangeConversion::_update_range() {
    _value_range = _max - _min;
}

void RangeConversion::_update_converted_range() {
    _converted_range = _target_max - _target_min;
}
