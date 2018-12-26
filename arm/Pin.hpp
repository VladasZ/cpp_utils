//
//  Pin.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 12/26/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#include "mbed.h"

class Pin : public DigitalIn {
public:

  using DigitalIn::DigitalIn;

  void wait_for_low()  { while  (read()); }
  void wait_for_high() { while (!read()); }

  void wait_for_change() {
	auto current = read();
	while (read() == current);
  }
};
