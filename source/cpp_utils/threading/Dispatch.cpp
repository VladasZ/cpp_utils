//
//  Dispatch.сpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 17/12/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#ifndef MICROCONTROLLER_BUILD

#include <mutex>
#include <thread>
#include <vector>

#include "Dispatch.hpp"

using namespace cu;

static std::mutex _mutex;

static std::vector<Dispatch::Task> _tasks;

void Dispatch::async(Task task) {
    std::thread(task).detach();
}

void Dispatch::on_main(Task task) {
    _mutex.lock();
    _tasks.push_back(task);
    _mutex.unlock();
}

void Dispatch::execute_tasks() {

    if (_tasks.empty()) {
        return;
    }

    _mutex.lock();
    for (const auto& task : _tasks) {
        task();
    }
    _tasks.clear();
    _mutex.unlock();
}

#endif