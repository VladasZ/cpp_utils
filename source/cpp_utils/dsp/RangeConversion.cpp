//
//  RangeConversion.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 07/05/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#include "RangeConversion.hpp"

using namespace cu;


RangeConversion::RangeConversion(float min, float max, float t_min, float t_max) {
    _min = min;
    _max = max;
    _target_min = t_min;
    _target_max = t_max;
    _update_converted_range();
    _check_clipping();
}

void RangeConversion::set_min(float min) {
    Log("HELLOYYYYY");
    _min = min;
    _check_clipping();
}

void RangeConversion::set_max(float max) {
    _max = max;
    _check_clipping();
}

void RangeConversion::set_target_min(float min) {
    _target_min = min;
    _update_converted_range();
}

void RangeConversion::set_target_max(float max) {
    _target_max = max;
    _update_converted_range();
}

void RangeConversion::set_clipping_range(float range) {
    _clipping_range = range;
    _check_clipping();
}

void RangeConversion::_check_clipping() {

    if (_log) {
        Logvar(_max);
        Logvar(_min);
        Logvar(_max > _min);
    }

    if (_max > _min) {
        _value_range = _max - _min;
        _is_clipping = false;
        return;
    }

    _is_clipping = true;
    _clip_shift = _max;
    _value_range = _clipping_range + _clip_shift - _min;

    if (_log) {
        Logvar(_clip_shift);
        Logvar(_value_range);

        Separator;
    }

}

void RangeConversion::_update_converted_range() {
    _converted_range = _target_max - _target_min;
}
