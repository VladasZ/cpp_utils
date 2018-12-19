//
//  Log.cpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 12/19/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#include "Log.hpp"

Serial *_serial_transmitter =
  []{
	auto serial = new Serial(USBTX, USBRX);
	serial->baud(57600);
	return serial;
  }();
