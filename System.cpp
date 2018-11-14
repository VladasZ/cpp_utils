//
//  System.cpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 8/20/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#ifdef APPLE
#include <unistd.h>
#include "CallObj.h"
#elif  WINDOWS
#include <ctime>
#include <Windows.h>
#endif

#include "Log.hpp"
#include "System.hpp"

void System::sleep(float interval) {
#ifdef APPLE
  usleep(interval * 1000000);
#elif WINDOWS
  Sleep(DWORD(interval * 1000));
#else 
  NOT_IMPLEMENTED;
#endif
}

int System::random() {
#ifdef APPLE
  return arc4random();
#else
  static bool flag = true;
  if (flag) {
	flag = false;
	srand((unsigned int)time(NULL));
  }
  return rand();
#endif
}

int System::random(int range) {
#ifdef APPLE
  return arc4random_uniform(range);
#else 
  return random() % range;
#endif
}

