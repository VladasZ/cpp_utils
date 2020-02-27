//
//  PathInfo.cpp
//  cpp_tools
//
//  Created by Vladas Zakrevskis on 27/02/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#include <utility>
#include <sys/stat.h>

#include "Log.hpp"
#include "PathInfo.hpp"

using namespace cu;
using namespace std;


static pair<bool, bool> get_info(const string& path) {
    static struct stat s;
    if (stat(path.c_str(), &s) == 0) {
        if (s.st_mode & S_IFDIR) {
            return { false, true };
        }
        if (s.st_mode & S_IFREG) {
            return { true, false };
        }
    }
    return { false, false };
}

PathInfo::PathInfo() {
    _is_valid     = false;
    _is_file      = false;
    _is_directory = false;
}

PathInfo::PathInfo(const string& path) {
  //  Log(path);
    auto info = get_info(path);
    _is_valid     = info.first || info.second;
    _is_file      = info.first;
    _is_directory = info.second;
}

std::string PathInfo::to_string() const {
    if (!_is_valid)    return "is not valid";
    if (_is_file)      return "is file";
    if (_is_directory) return "is directory";
}
