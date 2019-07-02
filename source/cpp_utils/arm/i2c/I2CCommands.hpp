//
//  I2CCommands.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 7/1/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#ifdef __arm__

namespace cu::I2C {

  enum Command : uint8_t {
      None,
	  WriteString,
	  spes,
  };
  
}

#endif
