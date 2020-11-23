//
//  CallObj.h
//  TestEngine
//
//  Created by Vladas Zakrevskis on 8/19/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#pragma once

#ifdef __APPLE__

#include <string>
#include <vector>


namespace obj_c {

    struct ScreenInfo {
        unsigned scale;
        unsigned refresh_rate;
        unsigned ppi;
        float res_x;
        float res_y;
    };

#ifdef IOS_BUILD
    ScreenInfo screen_info();
#endif

    std::string work_directory_path();

    void show_alert(const std::string& message);
    std::vector<std::string> ls(const std::string& path);

}

#endif
