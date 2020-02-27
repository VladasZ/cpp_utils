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

using namespace cu;

Path::Path(const char* path) : Path(std::string(path)) {

}

Path::Path(const std::string& path) : _path(path), _info(path) {

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
