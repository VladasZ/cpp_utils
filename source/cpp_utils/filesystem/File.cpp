//
//  File.cpp
//  cpp_tools
//
//  Created by Vladas Zakrevskis on 9/26/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#include <cstdio>
#include <fstream>
#include <sys/stat.h>

#include "Log.hpp"
#include "File.hpp"
#include "Target.hpp"
#include "WindowsInclude.hpp"
#include "FilesystemInclude.hpp"

using namespace cu;
using namespace std;


File::File(const string& path) : _path(path) {
    FILE* file = fopen(path.c_str(), "rb");
    if (file == nullptr) Fatal("Failed to open file: " + path);
    fseek(file, 0, SEEK_END);
    _size = static_cast<size_t>(ftell(file));
    fseek(file, 0, SEEK_SET);
    _data = new char[_size];
    fread(_data, 1, _size, file);
    fclose(file);
}

File::~File() {
    delete[] _data;
}

size_t File::size() const {
    return _size;
}

char* File::data() const {
    return _data;
}

string File::to_string() const {
    return string() +
        "\nFile: " + _path + "\nsize: " + ::to_string(_size) + "\n";
}

string File::read(const string& path) {
    ifstream stream(path.c_str(), ios::in);
    string result;

    if (stream.is_open()) {
        string line;
        while (getline(stream, line))
            result += "\n" + line;
        stream.close();
    }
    else {
        Fatal("Failed to open file: " + path);
    }

    return result;
}

bool File::exists(const std::string& path) {
    struct stat buffer = { };
    return (::stat(path.c_str(), &buffer) == 0);
}

std::string File::full_path(const std::string& path) {
#ifdef __MINGW32__
    return "File::full_path is not supported in MinGW yet.";
#elif IOS_BUILD
    return "File::full_path is not supported in iOS yet.";
#else
	return "File::full_path is not supported anywhere yet. =(";
#endif
}

void File::write(const std::string& path, const std::string& string) {
    std::ofstream outfile;
    outfile.open(path, std::ios_base::trunc);
    outfile << string;
}

void File::append(const std::string& path, const std::string& string) {
    std::ofstream outfile;
    outfile.open(path, std::ios_base::app);
    outfile << string;
}

void File::remove(const std::string& path) {
    ::remove(path.c_str());
}
