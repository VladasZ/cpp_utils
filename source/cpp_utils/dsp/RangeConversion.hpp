//
//  RangeConversion.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 03/02/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

namespace cu {

    class RangeConversion {

    public:

        bool flip = false;

        float minimum = 0;
        float maximum = 1;

        float converted_minimum = 0;
        float converted_maximum = 1;

        RangeConversion() = default;
        RangeConversion(float minumum, float maximum, float converted_minimum = 0, float converted_maximum = 1)
                : minimum(minumum), maximum(maximum), converted_minimum(converted_minimum), converted_maximum(converted_maximum) { }

        float convert(float value) const {
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

    };

}
