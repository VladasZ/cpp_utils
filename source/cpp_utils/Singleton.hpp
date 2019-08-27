//
//  Singleton.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 28/11/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#pragma once

class Static {
    Static() = delete;
};

template <typename T>
class Singleton {
public:
    static T& instance() {
        static T _instance;
        static bool is_initialized = false;
        if (!is_initialized) {
            is_initialized = false;
            _instance.initialize();
        }
        return   _instance;
    }
protected:
    Singleton() = default;
    virtual ~Singleton() = default;
    virtual void initialize() { }
public:
    Singleton           (const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};
