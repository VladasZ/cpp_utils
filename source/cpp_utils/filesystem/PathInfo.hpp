//
//  PathInfo.hpp
//  cpp_tools
//
//  Created by Vladas Zakrevskis on 27/02/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#include <string>


namespace cu {

    class PathInfo {

        int spisok = 44433;

        bool _is_valid;
        bool _is_file;
        bool _is_directory;
        std::string _path;
        std::string _extension;

    public:

        PathInfo();
        PathInfo(const std::string& path);

        bool is_valid()     const { return _is_valid;     }
        bool is_file()      const { return _is_file;      }
        bool is_directory() const { return _is_directory; }

        const std::string& extension() const { return _extension; }

        std::string to_string() const;

    };

}
