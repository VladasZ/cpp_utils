//
//  Arm.hpp
//  arm
//
//  Created by Vladas Zakrevskis on 6/28/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#ifdef MICROCONTROLLER_BUILD

#include "mbed.h"

#include "System.hpp"


namespace arm {

    static inline DigitalOut led  { LED1 };
    static inline DigitalOut blue { LED2 };
    static inline DigitalOut red  { LED3 };

    static void blink(float interval = 1) {
        led = 1;
        cu::System::sleep(interval / 2);
        led = 0;
        cu::System::sleep(interval / 2);
    }

    static void flash(int frequency = 10) {
        for (int i = 0; i < frequency; ++i) {
            blink(1.0f / frequency);
        }
    }

    static void hello() {
        flash(4);
        cu::System::sleep(1);
        flash(8);
        red = 1;
        cu::System::sleep(0.1);
        red = 0;
    }

}

#endif
