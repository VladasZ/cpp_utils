//
//  ClippingConversion.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 11/05/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#include "ClippingConversion.hpp"


using namespace cu;


ClippingConversion::ClippingConversion(float clipping_range) : _is_clipping(false), _middle_point(0), _clipping_range(clipping_range) {

}

void ClippingConversion::_update_range() {
    if (_max > _min) {
        _is_clipping = false;
        _value_range = _max - _min;
        return;
    }
    _middle_point = (_max + _min) / 2;
    _is_clipping = true;
    _value_range = _clipping_range + _max - _min;
}
