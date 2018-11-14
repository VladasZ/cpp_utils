//
//  File.cpp
//  cpp_tools
//
//  Created by Vladas Zakrevskis on 9/26/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#include "Log.hpp"
#include "File.hpp"

File::File(const char* path) {
    FILE* file = fopen(path, "rb");
    if (file == 0) {
        Error("Failed to open file: " << path);
        return;
    }
    fseek(file, 0, SEEK_END);
    _size = ftell(file);
    fseek(file, 0, SEEK_SET);
    _data = new char[_size];
    fread(_data, 1, _size, file);
    fclose(file);
}

File::~File() {
    delete[] _data;
}

size_t File::getSize() const {
    return _size;
}

char* File::getData() const {
    return _data;
}
