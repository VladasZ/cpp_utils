//
//  RangeConversion.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 03/02/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#include "Log.hpp"


namespace cu {

    class RangeConversion {

        bool _is_clipping = false;
        float _clip_shift = 0;
        float _clipping_range = 0;

        float _value_range = 1;
        float _converted_range = 1;

        float _min = 0;
        float _max = 1;

        float _target_min = 0;
        float _target_max = 1;

    public:

        bool _log = false;

        RangeConversion() = default;

        RangeConversion(float min, float max, float t_min = 0, float t_max = 1);

        float convert(float value) const {
            if (_log) {
                Logvar(_clip_shift);
                Logvar(value);
            }

            if (_is_clipping && value < _min) {
                value += _clip_shift;
            }

            if (_log) {
                Logvar(value);
                Separator;
            }

            auto normalized_value = (value - _min) / _value_range;

            return _converted_range * normalized_value + _target_min;
        }

        float min() const { return _min; }
        float max() const { return _max; }

        void set_min(float);
        void set_max(float);

        void set_target_min(float);
        void set_target_max(float);

        void set_clipping_range(float);

    private:

        void _check_clipping();
        void _update_converted_range();

    };

}
