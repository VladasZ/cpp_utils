//
//  ClippingConversion.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 11/05/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#include "RangeConversion.hpp"


namespace cu {

    class ClippingConversion : public RangeConversion {

        bool _is_clipping;
        float _middle_point;
        const float _clipping_range;

    public:

        ClippingConversion(float clipping_range) :
        _is_clipping(false),
        _middle_point(0),
        _clipping_range(clipping_range) { }

        float convert(float value) const override {
            if (_is_clipping && value < _middle_point) value += _clipping_range;
            return RangeConversion::convert(value);
        }

    private:

        void _update_range() override {
            if (_max > _min) {
                _is_clipping = false;
                _value_range = _max - _min;
                return;
            }
            _middle_point = (_max + _min) / 2;
            _is_clipping = true;
            _value_range = _clipping_range + _max - _min;
        }

    };

}
