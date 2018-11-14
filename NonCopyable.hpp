//
//  NonCopyable.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 19/01/2018.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

class NonCopyable {
protected:
    NonCopyable() = default;
    ~NonCopyable() = default;

    NonCopyable(NonCopyable const &) = delete;
    void operator=(NonCopyable const &) = delete;
};
