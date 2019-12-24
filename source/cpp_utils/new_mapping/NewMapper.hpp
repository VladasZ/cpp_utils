//
//  NewMapper.hpp
//  mapping
//
//  Created by Vladas Zakrevskis on 24/12/2019.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include <iostream>

#include "IterateTuple.hpp"

namespace new_mapping {

    template <class ClassesInfo>
    class Mapper {

        static_assert(cu::is_tuple<ClassesInfo>::value);

    public:

        const ClassesInfo classes_info;





    };

}
