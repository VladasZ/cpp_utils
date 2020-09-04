//
//  File.cpp
//  cpp_tools
//
//  Created by Vladas Zakrevskis on 9/26/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#define _CRT_SECURE_NO_WARNINGS

#include <fstream>

#include "Log.hpp"
#include "File.hpp"

using namespace std;

#ifdef ANDROID_BUILD

#include "AndroidSystem.hpp"

static pair<char*, size_t> read(const string& path) {
    auto file = AndroidSystem::load_file(path);
    return { file.first,  file.second };
}

static string read_to_string(const string& path) {
    auto file = AndroidSystem::load_file(path);
    return string(file.first, file.second);
}

#else

static pair<char*, size_t> read(const string& path) {
    FILE* file = fopen(path.c_str(), "rb");
    if (file == nullptr) {
        Fatal("Failed to open file: " + path);
    }
    fseek(file, 0, SEEK_END);
    auto size = static_cast<size_t>(ftell(file));
    fseek(file, 0, SEEK_SET);
    auto data = new char[size];
    fread(data, 1, size, file);
    fclose(file);
    return { data, size };
}

static std::string read_to_string(const string& path) {
    ifstream stream(path.c_str(), ios::in);
    string result;

    if (stream.is_open()) {
        string line = "";
        while (getline(stream, line))
            result += "\n" + line;
        stream.close();
    }
    else {
        Fatal("Failed to open file: " + path);
    }

    return result;
}

#endif

cu::File::File(char* data, size_t size) : _data(data), _size(size) {

}

cu::File::File(const string& path) : _path(path) {
    auto file = read(path);
    _data = file.first;
    _size = file.second;
}

cu::File::~File() {
    if (_data != nullptr) {
        delete[] _data;
    }
}

size_t cu::File::size() const {
    return _size;
}

char* cu::File::data() const {
    return _data;
}

string cu::File::to_string() const {
    return string() +
        "\nFile: " + _path + "\nsize: " + ::to_string(_size) + "\n";
}

string cu::File::read_to_string(const string& path) {
	return ::read_to_string(path);
}
