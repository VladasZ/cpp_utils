//
//  NumberBuffer.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 12/02/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#include <cstdint>

namespace cu {

    union NumberBuffer {
        uint64_t u64;
         int64_t i64;

        uint32_t u32[2];
         int32_t i32[2];

        uint16_t u16[4];
         int16_t i16[4];

        uint32_t u8[8];
         int32_t i8[8];
    };

}
