//
//  NewFile.hpp
//  cpp_tools
//
//  Created by Vladas Zakrevskis on 13/02/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#include <fstream>

namespace cu {

    struct FileData {
        uint8_t* data;
        size_t size;
    };

	class NewFile {

	    std::fstream* _stream_ptr = nullptr;
        std::fstream& _stream;

        FileData* _data;

	public:

	    NewFile(const std::string& path);
	    ~NewFile();


	    FileData* data() const;


    private:

        void _read(uint8_t* buffer, unsigned size);
        void _write(uint8_t* buffer, unsigned size);

	};

}
