//
//  File.hpp
//  cpp_tools
//
//  Created by Vladas Zakrevskis on 9/26/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#pragma once

#include <stddef.h>

namespace cu {

	class File {

		size_t _size = 0;
		char* _data = nullptr;

	public:

		size_t size() const;
		char* data() const;

		File() = default;
		File(const char* path);
		~File();

		static std::string read_to_string(const std::string& path);

	};

}
