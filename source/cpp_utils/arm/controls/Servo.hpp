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

        float _high = 2000;
        float _low  = 1000;
        float _range;

        PwmOut _pwm;

    public:

        Servo(PinName pin);

        void write(float percent);
        void disable();

        void wave(float range = 1.0f, float duration = 1.0f);

        void set_pulse_range(float high, float low);
        void set_pulse_width(float);

        Servo& operator= (float percent);

    };

}

#endif