//
//  NonCopyable.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 19/01/2018.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once


namespace cu {

    class NonCopyable {
    protected:
        NonCopyable() = default;
        ~NonCopyable() = default;

    private:
        NonCopyable(NonCopyable const&);
        const NonCopyable& operator=(NonCopyable const&);
    };

}
