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
        RangeConversion(float minumum, float maximum, float converted_minimum = 0, float converted_maximum = 1);

        float convert(float value) const;

    };

}
