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

        ClippingConversion(float clipping_range);

        float convert(float value) const override {
            if (_is_clipping && value < _middle_point) value += _clipping_range;
            return RangeConversion::convert(value);
        }

    private:

        void _update_range() override;

    };

}
