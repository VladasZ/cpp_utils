//
//  Path.hpp
//  cpp_tools
//
//  Created by Vladas Zakrevskis on 8/6/19.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#pragma once

#include <string>

namespace cu {
    
    class Path : public std::string {
        
    public:
        
        using std::string::string;
        
        Path(const std::string&);

        Path operator / (const Path&) const;

    };
    
}

