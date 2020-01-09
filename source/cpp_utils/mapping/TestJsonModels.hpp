//
//  TestJsonModels.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 9/01/2020.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#include "JSONMappable.hpp"

namespace mapping {

    class TestClass : public JSONMappable<TestClass> {

    public:

        int age = 100;
        float height = 111.11;

        static std::string_view class_name() { return "TestClass"; }

        static auto properties() {
            return std::make_tuple(
                    Property("age", &TestClass::age),
                    Property("height", &TestClass::height)
            );
        }

    };

}
