//
//  NewPath.cpp
//  cpp_tools
//
//  Created by Vladas Zakrevskis on 03/08/20.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#include "NewPath.hpp"

using namespace cu;


paths NewPath::ls(const std::string& path) {
	paths result;
	for (const auto& path : fs::directory_iterator(path)) {
		result.push_back(fs::canonical(path));
	}
	return result;
}

fs::path NewPath::pwd() {
	return fs::current_path();
}

void NewPath::write(const std::string& path, const std::string& text) {
	fs::ofstream stream { path, fs::ofstream::app };
	std::string new_line = text + "\n";
	stream.write(new_line.c_str(), new_line.size());
}

void NewPath::remove(const std::string& path) {
	fs::remove(path);
}