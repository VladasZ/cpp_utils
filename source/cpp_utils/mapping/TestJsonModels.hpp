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

    class TestClass //: public JSONMappable<TestClass>
            {

    public:

        uint8_t age = 100;
        uint8_t page = 110;
        uint8_t wage = 120;
        uint8_t gage = 130;


//        static std::string_view class_name() { return "TestClass"; }
//
//        static auto properties() {
//            return std::make_tuple(
//                    Property("age", &TestClass::age),
//                    Property("height", &TestClass::height)
//            );
//        }

    };

}
