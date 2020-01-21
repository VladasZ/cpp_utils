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

namespace arm {

    static DigitalOut led(LED1);

    void blink(float interval = 1);
    void flash(int frequency = 10);
    void hello();

}

#endif
