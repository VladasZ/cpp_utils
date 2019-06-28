//
//  Pin.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 6/28/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#ifdef __arm__

#include "mbed.h"

namespace cu::arm {

  template <class PinType>
  void blink(PinType& pin, float frequency = 1) {
	pin = 1;
	wait(frequency / 2);
	pin = 0;
	wait(frequency / 2);
  }

}

#endif
