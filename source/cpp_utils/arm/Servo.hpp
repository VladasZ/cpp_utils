//  Servo.hpp
//  arm
//
//  Created by Vladas Zakrevskis on 17/01/10.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#ifdef MICROCONTROLLER_BUILD

#include "mbed.h"

namespace arm {

    class Servo {

        const float _high;
        const float _low;
        const float _range;

        PwmOut _pwm;

    public:

        Servo(PinName pin, float high, float low);

        void write(float percent);
        void disable();

        void wave(float range = 1.0f, float duration = 1.0f);

        Servo& operator= (float percent);

    };

}

#endif
