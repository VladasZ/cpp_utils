//
//  Dispatch.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 17/12/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#ifndef MICROCONTROLLER_BUILD

#include <functional>

namespace cu {

    class Dispatch {

    public:

        using Task = std::function<void()>;

        static void async(Task);
        static void on_main(Task);

        static void execute_tasks();

    };

}

#endif