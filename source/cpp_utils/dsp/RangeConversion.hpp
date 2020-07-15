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

    protected:

        float _value_range = 1;
        float _converted_range = 1;

        float _min = 0;
        float _max = 1;

        float _target_min = 0;
        float _target_max = 1;

    public:

        bool flip = false;

        virtual float convert(float value) const {
            auto normalized_value = (value - _min) / _value_range;
            auto result = _converted_range * normalized_value + _target_min;
            if (flip) {
                result = _converted_range - result;
            }
            return result;
        }

        float convert_back(float value) const {
            return value / _target_max;
        }

        float min() const { return _min; }
        float max() const { return _max; }

        void set_min(float min) { _min = min; _update_range(); }
        void set_max(float max) { _max = max; _update_range(); }

        void set_target_min(float min) { _target_min = min; _update_converted_range(); }
        void set_target_max(float max) { _target_max = max; _update_converted_range(); }

    protected:

        virtual void _update_range() { _value_range = _max - _min; }
        void _update_converted_range() { _converted_range = _target_max - _target_min; }

    };

}
