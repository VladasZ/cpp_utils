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

Path::Path(const char* path) : Path(std::string(path)) {

}

Path::Path(const std::string& path) : _path(path), _info(path) {

}

void Path::trim_relative() {
    auto last_component = Log::last_path_component(_path);
    if (last_component == "..") {
        String::drop_last(_path, 3);
        auto folder_name = Log::last_path_component(_path);
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
    return Path(this->_path + "/" + path._path);
}

Path::operator std::string() const {
    return _path;
}

Path::Array Path::ls() const {
    return System::ls(this->_path);
}

std::string Path::file_name() const {
    return Log::last_path_component(_path);
}

std::string Path::to_string() const {
    return std::string() +
    "Path: " + this->_path + " " + _info.to_string();
}
