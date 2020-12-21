//
//  Result.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 9/4/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include "Log.hpp"


namespace cu {

    template<class T>
    class Result {

        bool _found;
        T _object;

    public:

        const std::optional<std::string> error;

        constexpr Result() : _found(false) { }

        constexpr Result(const T& object) : _found(true), _object(object) { }

        constexpr bool found()     const { return  _found; }
        constexpr bool not_found() const { return !_found; }

        constexpr bool ok() const { return _found; }
        constexpr bool errored() const { return !_found; }

        constexpr const T& object() const {
            if (not_found()) Fatal("Conversion of not found result of type: " + cu::class_name<T>());
            return _object;
        }

        constexpr operator const T&() const {
            return object();
        }

    };

}
