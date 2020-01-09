//
//  Arm.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 6/28/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#ifdef MICROCONTROLLER_BUILD

namespace cu::Arm {

    void blink(float interval = 1);
    void flash(int frequency = 10);

}

#endif
