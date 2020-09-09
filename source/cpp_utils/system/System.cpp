//
//  System.cpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 8/20/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#ifdef APPLE
#include "CallObj.hpp"
#endif

#ifdef _WIN32
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
#include <direct.h>
#include <windows.h>
#include <Lmcons.h>
#else
#include <unistd.h>
#include "dirent.h"
#endif

#include "Log.hpp"
#include "System.hpp"
#include "ExceptionCatch.hpp"

using namespace cu;
using namespace std;


void System::alert(const std::string& message) {
#ifdef _WIN32
    MessageBox(0, message.c_str(), "System alert.", MB_OK);
#elif APPLE
    obj_c::show_alert(message);
#else
    Log << "System::alert is not implemented for this platform.";
    Log << message;
#endif
}

#ifndef MICROCONTROLLER_BUILD

const Path System::user_name() {
    static const Path user = [] {
#if (_WIN32)
        char username[UNLEN + 1];
        DWORD username_len = UNLEN + 1;
        GetUserName(username, &username_len);
        return std::string(username);
#elif IOS_BUILD
        return "NOT IMPLEMENTED FOR THIS PLATFORM";
#elif ANDROID_BUILD
        return "NOT IMPLEMENTED FOR THIS PLATFORM";
#else
        auto _user = getenv("USER");
        if (!_user) {
            return Path("No USER enviroment variable.");
        }
        return Path(string(_user));

#endif
    }();

    return user;
}

const Path& System::home() {
    static const Path result = [] {
#ifdef _WIN32
        Path users{ "C:/Users" };
#elif APPLE
        Path users{ "/Users" };
#else
        Path users{ "/home" };
#endif
        return users / user_name();
    }();
    return result;
}

Path System::pwd() {
#ifdef _WIN32
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
    return Path{ cwd };
#endif
}


std::vector<Path> System::ls(const std::string& path) {
#ifdef _WIN32
    std::vector<Path> names;
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
    std::vector<Path> result;
    auto dir = opendir(path.c_str());
    if (!dir) {
        Fatal("Path not found " + path);
    }
    dirent* ent = nullptr;
    while ((ent = readdir(dir))) {
        if (!strcmp(ent->d_name, ".") || !strcmp(ent->d_name, "..")) {
            continue;
        }
        result.emplace_back(path + "/" + ent->d_name);
    }
    closedir(dir);
    return result;
#endif
}

void System::execute(const std::string& command) {
#ifndef _WIN32
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    }
    catch (...) {
        pclose(pipe);
        Fatal(what());
    }
    pclose(pipe);
    Log << result;
#else
	Log << "Executing:" << command << "is not implemented on this platform.";
#endif
}

#endif

#ifdef _WIN32

vector<string> System::get_com_ports() {

    static TCHAR path[5000];

    vector<string> result;

    for (auto i = 0; i < 255; i++) {
        std::string name = "COM" + std::to_string(i);

        if (QueryDosDevice(name.c_str(), (LPSTR)path, 5000)) {
            result.push_back(name);
        }

    }

    return result;

}

#endif