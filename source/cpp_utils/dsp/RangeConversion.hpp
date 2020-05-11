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

        float _value_range = 1;
        float _converted_range = 1;

        float _min = 0;
        float _max = 1;

        float _target_min = 0;
        float _target_max = 1;

    public:

        bool flip = false;

        RangeConversion() = default;

        RangeConversion(float min, float max, float t_min = 0, float t_max = 1);

        float convert(float value) const {
            auto normalized_value = (value - _min) / _value_range;
            auto result = _converted_range * normalized_value + _target_min;
            if (flip) {
                result = _converted_range - result;
            }
            return result;
        }

        float min() const { return _min; }
        float max() const { return _max; }

        void set_min(float);
        void set_max(float);

        void set_target_min(float);
        void set_target_max(float);

    private:

        void _update_range();
        void _update_converted_range();

    };

}
