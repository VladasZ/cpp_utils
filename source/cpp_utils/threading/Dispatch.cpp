//
//  Dispatch.сpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 17/12/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#ifndef MICROCONTROLLER_BUILD

#include <thread>

#include "Dispatch.hpp"

using namespace cu;
using namespace std;


void Dispatch::async(Task task) {
    thread(task).detach();
}

void Dispatch::on_main(Task task) {
    lock_guard lock(_mutex);
    _tasks.push_back(task);
}

void Dispatch::execute_tasks() {
    if (_tasks.empty()) return;

    lock_guard lock(_mutex);
    for (const auto& task : _tasks) {
        task();
    }
    _tasks.clear();
}

#endif
