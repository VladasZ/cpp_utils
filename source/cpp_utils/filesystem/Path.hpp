//
//  Path.hpp
//  cpp_tools
//
//  Created by Vladas Zakrevskis on 8/6/19.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#pragma once

#ifndef MICROCONTROLLER_BUILD

#include <string>
#include <vector>

#include "PathInfo.hpp"


namespace cu {

    class Path {

        PathInfo _info;
        std::string _path;

    public:

        using Array = std::vector<Path>;

        Path() = default;
        Path(const char*);
        Path(const std::string&);

        bool is_valid()     const { return _info.is_valid();     }
        bool is_file()      const { return _info.is_file();      }
        bool is_directory() const { return _info.is_directory(); }

        const std::string& extension() const { return _info.extension(); }

        void trim_relative();

        Path operator / (const Path&) const;

        operator std::string() const;

        Array ls() const;

        std::string file_name() const;

        std::string to_string() const;

    };
    
}

#endif
