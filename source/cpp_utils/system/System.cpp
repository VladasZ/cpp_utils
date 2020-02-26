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

#ifdef APPLE
#include "CallObj.hpp"
#endif

#include <unistd.h>


#include "Log.hpp"
#include "System.hpp"

using namespace cu;
using namespace std;

void System::sleep(double interval) {
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

void System::alert(const std::string& message) {
#ifdef WINDOWS
    MessageBox(0, message.c_str(), "System alert.", MB_OK);
#elif APPLE
    obj_c::show_alert(message);
#else
    Log("System::alert is not implemented for this platform.");
    Log(message);
#endif
}

string System::user_name() {
#ifdef WINDOWS
    char username[UNLEN + 1];
    DWORD username_len = UNLEN + 1;
    GetUserName(username, &username_len);
    return username;
#elif IOS_BUILD
    Fatal("NOT IMPLEMENTED FOR THIS PLATFORM");
#elif ANDROID_BUILD
    Fatal("NOT IMPLEMENTED FOR THIS PLATFORM");
#else
    auto user = getenv("USER");
    if (!user) {
        return Path("No USER enviroment variable.");
    }
    return string(user);
#endif
}

Path System::home() {
#ifdef WINDOWS
    Path users = "C:/Users";
#elif APPLE
    Path users = "/Users";
#else
    Path users = "/home";
#endif
    return users / user_name();
}

Path System::pwd() {
#ifdef DESKTOP_BUILD
    char cwd[1024];
    chdir("/path/to/change/directory/to");
    getcwd(cwd, sizeof(cwd));
    printf("Current working dir: %s\n", cwd);
    return cwd;
#else
    return "Not implemented on this platform";
#endif
}

#include "dirent.h"

Path::Array System::ls(const std::string& path, bool full_path) {
#ifdef DESKTOP_BUILD
    Path::Array result;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir("c:\\src\\")) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            result.push_back(ent->d_name);
        }
        closedir(dir);
    }
    else {
        perror ("");
        throw std::runtime_error("Path not found" + path);
    }
    return result;
#else
    return { "Not implemented on this platform" };
#endif
}

