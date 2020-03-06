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


#ifdef APPLE
#include "CallObj.hpp"
#endif

#ifdef DESKTOP_BUILD
#ifdef WINDOWS_BUILD
#include <stdio.h>
#include <direct.h>
#include <windows.h>
#include <Lmcons.h>
#else
#include <unistd.h>
#include "dirent.h"
#endif
#endif


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

const Path System::user_name() {
    static const Path user = [] {
#ifdef WINDOWS
        char username[UNLEN + 1];
        DWORD username_len = UNLEN + 1;
        GetUserName(username, &username_len);
        return username;
#elif IOS_BUILD
        return "NOT IMPLEMENTED FOR THIS PLATFORM";
#elif ANDROID_BUILD
        return "NOT IMPLEMENTED FOR THIS PLATFORM";
#else
        auto user = getenv("USER");
        if (!user) {
            return Path("No USER enviroment variable.");
        }
        return Path(string(user));
    }();

#endif
    return user;
}

const Path& System::home() {
    static const Path result = [] {
#ifdef WINDOWS
        Path users { "C:/Users" };
#elif APPLE
        Path users { "/Users" };
#else
        Path users { "/home" };
#endif
        Logvar(users);
        return users / user_name();
    }();
    return result;
}

Path System::pwd() {
#ifdef DESKTOP_BUILD
#ifdef WINDOWS_BUILD
    static char cCurrentPath[FILENAME_MAX];
    if (!_getcwd(cCurrentPath, sizeof(cCurrentPath))) {
        Fatal("");
    }
    cCurrentPath[sizeof(cCurrentPath) - 1] = '\0';
    return cCurrentPath;
#else
    char cwd[1024];
    chdir("/path/to/change/directory/to");
    getcwd(cwd, sizeof(cwd));
    printf("Current working dir: %s\n", cwd);
    return Path { cwd };
#endif
#else
    return "Not implemented on this platform";
#endif
}


Path::Array System::ls(const std::string& path, bool full_path) {
#ifdef DESKTOP_BUILD
#ifdef WINDOWS_BUILD
    Path::Array names;
    string search_path = path + "/*.*";
    WIN32_FIND_DATA fd;
    HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                names.push_back(fd.cFileName);
            }
        } while (::FindNextFile(hFind, &fd));
        ::FindClose(hFind);
    }
    return names;
#else
    Path::Array result;
    auto dir = opendir(path.c_str());
    if (!dir) {
        Fatal("Path not found " + path);
    }
    dirent* ent = nullptr;
    while ((ent = readdir(dir))) {
        result.emplace_back(path + "/" + ent->d_name);
    }
    closedir(dir);
    return result;
#endif
#else
    return { "Not implemented on this platform" };
#endif
}
