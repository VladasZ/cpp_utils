//
//  Result.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 9/4/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include <string>

namespace cu {

    template<class T>
    class Result {

    public:

        bool found;
        T result;

        Result() : found(false) {

        }

        Result(const T& result) : result(result), found(true) {

        }

        operator T() const {
            if (!found) {
                throw std::runtime_error(std::string() +
                                         "Conversion of not found result of type: " + typeid(T).name());
            }
            return result;
        }

        std::string to_string() {
            if (found) {
                return std::string() + "\n" +
                       "Found result: " "\n"
                       + result.to_string();
            }
            return "Not found result";
        }

    };

}
