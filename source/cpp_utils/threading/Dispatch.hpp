//
//  Dispatch.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 17/12/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include <mutex>
#include <vector>
#include <functional>


namespace cu {

    class Dispatch {

    public:

		static inline bool enabled = true;

        using Task = std::function<void()>;

        static void async(Task);
        static void on_main(Task);

        static void execute_tasks();

        static void each(float delay, Task);

    private:

        static inline std::mutex _mutex;
        static inline std::vector<Task> _tasks;

    };

}
