
#pragma once

#include <stdint.h>

namespace cu {

template <class T>
class DataPacket {
public:

  using HeaderType = uint32_t;

  static inline HeaderType header_value = 0b11101011'10011001;

  HeaderType header = DataPacket::header_value;
  T payload;
};

}
