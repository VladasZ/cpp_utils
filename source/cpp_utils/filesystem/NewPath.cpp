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
