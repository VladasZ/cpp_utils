//
//  NewFile.cpp
//  cpp_tools
//
//  Created by Vladas Zakrevskis on 13/02/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#include "NewFile.hpp"

using namespace cu;
using namespace std;

NewFile::NewFile(const std::string& path) : _stream_ptr(new fstream()), _stream(*_stream_ptr) {
    _stream.open(path, ios::out | ios::in | ios::binary);
}

NewFile::~NewFile() {
    delete _data->data;
    delete _data;
    _stream.close();
    delete _stream_ptr;
}

FileData* NewFile::data() const {
    return nullptr;
}
