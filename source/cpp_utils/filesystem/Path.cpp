//
//  Path.cpp
//  cpp_tools
//
//  Created by Vladas Zakrevskis on 8/6/19.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#include "Log.hpp"
#include "Path.hpp"
#include "System.hpp"
#include "StringUtils.hpp"

using namespace cu;


Path::Path(const char* path) {
    if (!path) {
        Fatal("Path init from nullptr");
    }
    _path = path;
#ifdef _WIN32
    String::replace('\\', '/', _path);
#endif
    _info = _path;
}

Path::Path(const std::string& path)  {
    _path = path;
#ifdef _WIN32
    String::replace('\\', '/', _path);
#endif
    _info = _path;
}

void Path::trim_relative() {
    auto last_component = String::last_path_component(_path);
    if (last_component == "..") {
        String::drop_last(_path, 3);
        auto folder_name = String::last_path_component(_path);
        String::drop_last(_path, folder_name.size() + 1);
    }
    else if (last_component == ".") {
        String::drop_last(_path, 2);
    }
    _info = _path;
}

Path Path::operator / (const Path& path) const {
    if (path._path.empty()) {
        return *this;
    }
    if (this->_path.empty()) {
        return path;
    }
    return Path(_path + "/" + path._path);
}

Path::operator std::string() const {
    return _path;
}

std::vector<Path> Path::ls() const {
    return System::ls(_path);
}

Path Path::parent() const {
    auto last_part = String::last_path_component(_path);
    std::string parent = _path;
    String::drop_last(parent, last_part.size() + 1);
    return parent;
}

std::string Path::file_name() const {
    return String::last_path_component(_path);
}

std::string Path::to_string() const {
    return VarString(_path) + ", " + VarString(_info);
}
