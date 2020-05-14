//  Servo.hpp
//  arm
//
//  Created by Vladas Zakrevskis on 17/01/10.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#ifdef MICROCONTROLLER_BUILD

#include "Servo.hpp"

using namespace arm;


Servo::Servo(PinName pin) : _range(_high - _low), _pwm(pin) { }

void Servo::write(float percent) {
    set_pulse_width(_low + percent * _range);
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

void Servo::set_pulse_range(float high, float low) {
    _high = high;
    _low = low;
    _range = high - low;
}

void Servo::set_pulse_width(float width) {
    _pwm.pulsewidth(width / 1000000.0f);
}

Servo& Servo::operator=(float percent) {
    write(percent);
    return *this;
}

#endif
