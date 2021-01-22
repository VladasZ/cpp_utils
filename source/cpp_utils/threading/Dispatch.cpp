//
//  Dispatch.сpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 17/12/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#include <thread>

#include "System.hpp"
#include "Dispatch.hpp"

using namespace cu;
using namespace std;


void Dispatch::async(Task task) {
	if (enabled) {
		thread(task).detach();
	}
	else {
		task();
	}
}

void Dispatch::on_main(Task task) {
	if (enabled) {
		lock_guard lock(_mutex);
		_tasks.push_back(task);
	}
	else {
		task();
	}
}

void Dispatch::execute_tasks() {

	if (!enabled) return;

    if (_tasks.empty()) return;

    lock_guard lock(_mutex);
    for (const auto& task : _tasks) {
        task();
    }
    _tasks.clear();
}

void Dispatch::each(float delay, Task task) {
	thread([=] {
	    while (true) {
            task();
            System::sleep(delay);
	    }
	}).detach();
}
