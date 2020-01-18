//  Servo.hpp
//  arm
//
//  Created by Vladas Zakrevskis on 17/01/10.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#ifdef MICROCONTROLLER_BUILD

#include "Servo.hpp"
#include "GmMath.hpp"

using namespace arm;

Servo::Servo(PinName pin, float high, float low)
: _high(high), _low(low), _range(high - low), _pwm(pin) { }

void Servo::write(float percent) {
    _pwm.pulsewidth(_low + percent * _range);
}

void Servo::disable() {
    _pwm.pulsewidth(0);
}

void Servo::wave(float range, float duration) {
    write(range);
    wait(duration / 2);
    write(0);
    wait(duration / 2);
}

Servo& Servo::operator=(float percent) {
    write(percent);
    return *this;
}

#endif
