//
//  Utils.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 7/1/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

namespace cu::utils {

  template <class T>
  void increment_with_limit(T& value, size_t limit = 10) {
	value++;
	if (value == limit)
	  value = 0;
  }

}
