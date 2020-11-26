//
//  Random.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 26/11/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#include <time.h>    
#include <stdlib.h>


namespace cu {

#ifndef __APPLE__
	class _Random { public:
        _Random() {  srand(static_cast<unsigned>(time(nullptr))); }
        static inline int random() { return rand(); }
	};
    static const inline auto _random = _Random();
#endif

    static inline int random() {
#ifdef __APPLE__
        return arc4random();
#else
        return _random.random();
#endif
    }

    static inline int random(int range) {
        return random() % range;
    }

}
