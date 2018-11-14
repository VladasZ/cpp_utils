//
//  System.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 8/19/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#pragma once

class System {
    
    System();
    
public:
    
    static void sleep(float interval);
    static int random();
    static int random(int range);
};
