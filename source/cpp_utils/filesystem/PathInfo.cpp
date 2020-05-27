//
//  PathInfo.cpp
//  cpp_tools
//
//  Created by Vladas Zakrevskis on 27/02/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#ifndef MICROCONTROLLER_BUILD
#include <utility>
#include <sys/stat.h>
#endif

#include "Log.hpp"
#include "PathInfo.hpp"

using namespace cu;
using namespace std;

struct _Info {
    bool is_file = false;
    bool is_dir  = false;
};

static _Info get_info(const string& path) {
#ifdef MICROCONTROLLER_BUILD
    return { };
#else
    struct stat s;
    if (stat(path.c_str(), &s) != 0) return { };

    _Info info;
    info.is_dir  = s.st_mode & S_IFDIR;
    info.is_file = s.st_mode & S_IFREG;
    return info;

#endif
}

static std::string get_extension(const string& path) {
    auto index = path.rfind('.');
    if (index == string::npos) return { };
    return path.substr(index + 1);
}

PathInfo::PathInfo() {
    _is_valid     = false;
    _is_file      = false;
    _is_directory = false;
}

PathInfo::PathInfo(const string& path) {
    auto info = get_info(path);
    _is_valid     = info.is_file || info.is_dir;
    _is_file      = info.is_file;
    _is_directory = info.is_dir;
    _extension = get_extension(path);
    _path = path;
}

std::string PathInfo::to_string() const {
    return VarString(_is_valid) + ", " + VarString(_is_file) + ", " + VarString(_is_directory) + ", " + VarString(spisok);
}
