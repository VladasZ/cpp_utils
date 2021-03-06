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

#ifdef ANDROID_BUILD
#include "AndroidSystem.hpp"
#endif

using namespace cu;
using namespace std;


File::File(const string& path) : _path(path) {
#ifdef ANDROID_BUILD
    auto file_data = AndroidSystem::load_file(path);
    _data = file_data.first;
    _size = file_data.second;
#else
    FILE* file = fopen(path.c_str(), "rb");
    if (file == nullptr) Fatal("Failed to open file: " + path);
    fseek(file, 0, SEEK_END);
    _size = static_cast<size_t>(ftell(file));
    fseek(file, 0, SEEK_SET);
    _data = new char[_size];
    fread(_data, 1, _size, file);
    fclose(file);
#endif
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
#ifdef ANDROID_BUILD
    auto file_data = AndroidSystem::load_file(path);
    return { file_data.first, file_data.second };
#else
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
#endif
}

bool File::exists(const std::string& path) {
    struct stat buffer = { };
    return (::stat(path.c_str(), &buffer) == 0);
}

std::string File::full_path(const std::string& path) {
#ifdef CU_USING_FILESYSTEM
	return std::filesystem::canonical(path).u8string();
#else
	return "File::full_path is not supported on this platform yet.";
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
