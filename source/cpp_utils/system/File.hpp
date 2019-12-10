//
//  File.hpp
//  cpp_tools
//
//  Created by Vladas Zakrevskis on 9/26/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#pragma once

namespace cu {

	class File {

		std::string _path;
		char* _data = nullptr;
        unsigned _size;

	public:

		File(char* data, unsigned size);
		File(const std::string& path);
		~File();

        unsigned size() const;
		char* data() const;

		std::string to_string() const;

		static std::string read_to_string(const std::string& path);

	};

}
