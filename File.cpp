//
//  File.cpp
//  cpp_tools
//
//  Created by Vladas Zakrevskis on 9/26/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#include "Log.hpp"
#include "File.hpp"


ut::File::File(const char* path) {
    FILE* file = fopen(path, "rb");
    if (file == nullptr) {
        Error("Failed to open file: " << path);
        return;
    }
    fseek(file, 0, SEEK_END);
    _size = static_cast<size_t>(ftell(file));
    fseek(file, 0, SEEK_SET);
    _data = new char[_size];
    fread(_data, 1, _size, file);
    fclose(file);
}

ut::File::~File() {
    delete[] _data;
}

size_t ut::File::size() const {
    return _size;
}

char* ut::File::data() const {
    return _data;
}
