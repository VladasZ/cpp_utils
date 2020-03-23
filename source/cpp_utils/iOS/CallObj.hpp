//
//  CallObj.h
//  TestEngine
//
//  Created by Vladas Zakrevskis on 8/19/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#pragma once

#ifdef APPLE

#include <string>
#include <vector>

namespace obj_c {

    extern const std::string work_directory_path;
    
    void show_alert(const std::string& message);
    std::vector<std::string> ls(const std::string& path);

    void test_central();
    void test_peripheral();

}

#endif
