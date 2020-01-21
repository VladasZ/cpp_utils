//
//  Arm.cpp
//  arm
//
//  Created by Vladas Zakrevskis on 9/01/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#ifdef MICROCONTROLLER_BUILD

#include "Arm.hpp"

void arm::blink(float interval) {
    led = 1;
    wait(interval / 2);
    led = 0;
    wait(interval / 2);
}

void arm::flash(int frequency) {
    for (int i = 0; i < frequency; ++i) {
        blink(1.0f / frequency);
    }
}

void arm::hello() {
    arm::flash(4);
    wait(1);
    arm::flash(4);
    wait(1);
}

#endif
