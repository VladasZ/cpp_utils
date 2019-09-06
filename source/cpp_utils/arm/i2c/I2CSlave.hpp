//
//  I2CSlave.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 7/1/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include "System.hpp"

#ifdef MICROCONTROLLER_BUILD

#include "Utils.hpp"
#include "I2CCommands.hpp"

namespace cu {

class I2CSlave {

  void* _interface;

  I2C::Command _command = I2C::Command::None;
  
public:

  I2CSlave(PinName sda, PinName scl);
  
  void set_address(int);
  void start_listening(Callback = nullptr);

};

}

#endif
