//
//  JsonInclude.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 09/10/2020.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#if __has_include(<nlohmann/json.hpp>)
#include <nlohmann/json.hpp>
#define USING_JSON
#endif
