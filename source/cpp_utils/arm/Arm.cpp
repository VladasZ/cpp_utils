//
//  Arm.cpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 9/01/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#ifdef MICROCONTROLLER_BUILD

#include "mbed.h"

#include "Arm.hpp"

using namespace cu;

static DigitalOut led(LED1);

void Arm::blink(float interval) {
    led = 1;
    wait(interval / 2);
    led = 0;
    wait(interval / 2);
}

void Arm::flash(int frequency) {
    for (int i = 0; i < frequency; ++i) {
        blink(1.0f / frequency);
    }
}

#endif
