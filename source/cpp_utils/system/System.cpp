//
//  System.cpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 8/20/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#ifdef MICROCONTROLLER_BUILD
#include "mbed.h"
#else
#include <thread>
#endif

#ifdef WINDOWS
#include <windows.h>
#include <Lmcons.h>
#endif

#include "Log.hpp"
#include "System.hpp"

using namespace cu;

void System::sleep(float interval) {
#ifdef MICROCONTROLLER_BUILD
  wait(interval);
#else
  std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<uint64_t>(interval * 1000)));
#endif
}

unsigned System::random() {
#ifdef APPLE
  return arc4random();
#else
  static bool first_call = true;
  if (first_call) {
	first_call = false;
    srand(static_cast<unsigned>(time(nullptr)));
  }
  return rand();
#endif
}

unsigned System::random(unsigned range) {
#ifdef APPLE
  return arc4random_uniform(range);
#else 
  return random() % range;
#endif
}

Path System::user_name() {
#ifdef WINDOWS
	char username[UNLEN + 1];
	DWORD username_len = UNLEN + 1;
	GetUserName(username, &username_len);
    return username;
#elif IOS_BUILD
	Error("NOT IMPLEMENTED FOR THIS PLATFORM");
    return "System::user_name() is not implemented fot this platform";
#else
    auto user = getenv("USER");
    if (!user)
        return Path("No USER enviroment variable.");
    return Path(user);

#endif
}

void System::alert(const std::string& message) {
#ifdef WINDOWS
	MessageBox(0, message.c_str(), "System alert.", MB_OK);
#else
	Error("NOT IMPLEMENTED FOR THIS PLATFORM");
#endif
}
