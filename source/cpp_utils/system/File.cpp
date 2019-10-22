//
//  File.cpp
//  cpp_tools
//
//  Created by Vladas Zakrevskis on 9/26/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#include <fstream>

#include "Log.hpp"
#include "File.hpp"

using namespace cu;
using namespace std;

File::File(const char* path) {
    FILE* file = fopen(path, "rb");
    if (file == nullptr) {
        _Error("Failed to open file: " << path);
        return;
    }
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

std::string File::read_to_string(const std::string& path) {
	ifstream stream(path.c_str(), ios::in);
	std::string result;

	if (stream.is_open()) {
		std::string line = "";
		while (getline(stream, line))
			result += "\n" + line;
		stream.close();
	}
	else {
		throw std::runtime_error(std::string() + "Impossible to open file: " + path);
	}

	return result;
}
