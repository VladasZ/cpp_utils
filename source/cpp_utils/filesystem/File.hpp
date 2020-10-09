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
        size_t _size;

	public:

		explicit File(const std::string& path);
		~File();

		size_t size() const;
		char* data() const;

		std::string to_string() const;

		static bool exists(const std::string& path);
        static std::string full_path(const std::string& path = ".");

		static std::string read(const std::string& path);
        static void write(const std::string& path, const std::string& string);
		static void append(const std::string& path, const std::string& string);
		static void remove(const std::string& path);

	};

}
