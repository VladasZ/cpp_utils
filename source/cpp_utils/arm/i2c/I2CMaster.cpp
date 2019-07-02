//
//  I2CMaster.cpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 7/1/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#ifdef __arm__

#include "mbed.h"
#include "I2CMaster.hpp"
#include "I2CCommands.hpp"

using MbedI2CMaster = ::I2C;

using namespace cu;


I2CMaster::I2CMaster(PinName sda, PinName scl) {
  _interface = new MbedI2CMaster(sda, scl);
}

void I2CMaster::set_write_address(int address) {
  _current_address = address;
}

int I2CMaster::write_string(const std::string& str) {
  write(I2C::Command::WriteString);
  write(str.size());
  _write(std.c_str(), str.size());
}

int I2CMaster::read(char* data, int length) {
  return static_cast<MbedI2CMaster*>(_interface)->read(_current_address, data, length);
}

int I2CMaster::_write(const char* data, int length) {
  return static_cast<MbedI2CMaster*>(_interface)->write(_current_address, data, length);
}

#endif
