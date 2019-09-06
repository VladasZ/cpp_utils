//
//  I2CSlave.cpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 7/1/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//


#ifdef MICROCONTROLLER_BUILD

#include "mbed.h"
#include "I2CSlave.hpp"

using MbedI2CSlave = ::I2CSlave;

using namespace cu;

cu::I2CSlave::I2CSlave(PinName sda, PinName scl) {
  _interface = new MbedI2CSlave(sda, scl);
}
  
void cu::I2CSlave::set_address(int address) {
  static_cast<MbedI2CSlave*>(_interface)->address(address);
}

void cu::I2CSlave::start_listening(Callback callback) {

  auto i2c = static_cast<MbedI2CSlave*>(_interface);

  while(true) {
  
  switch (i2c->receive()) {
  case MbedI2CSlave::ReadAddressed:
	i2c->write("spoki", 6);
	if (callback)
	  callback();
	break;
  case MbedI2CSlave::WriteAddressed:
	//slave.read(buffer, 6);
	break;
  }
  }
}

#endif
