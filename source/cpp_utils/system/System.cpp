//
//  System.cpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 8/20/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#ifdef __arm__
#include "mbed.h"
#else
#include <thread>
#endif

#include "Log.hpp"
#include "System.hpp"

void System::sleep(float interval) {
#ifdef __arm__
  wait(interval);
#else
  std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<uint64_t>(interval * 1000)));
#endif
}

unsigned int System::random() {
#ifdef APPLE
  return arc4random();
#else
  static bool flag = true;
  if (flag) {
	flag = false;
    srand(static_cast<unsigned int>(time(nullptr)));
  }
  return rand();
#endif
}

unsigned int System::random(unsigned int range) {
#ifdef APPLE
  return arc4random_uniform(range);
#else 
  return random() % range;
#endif
}

std::string System::user_name() {
#ifdef _WIN32
    return "System::user_name() is not implemented fot this platform";
#elif IOS_BUILD
    return "NOT_IMPLEMENTED";
#else
    return getenv("USER");
#endif
}

