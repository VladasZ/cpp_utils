//
//  RangeConversion.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 03/02/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

namespace cu {

    class RangeConversion {

        float _value = 0;

    public:

        bool flip = false;

        float begin = 0;
        float end   = 1;

        float converted_begin = 0;
        float converted_end   = 1;

        RangeConversion() = default;
        RangeConversion(float begin, float end, float converted_begin = 0, float converted_end = 1);

        float convert(float);

        void operator = (float value);
        operator float();

    };

}
