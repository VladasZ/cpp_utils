//
//  BoxInclude.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 07/10/2020.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#if __has_include(<box2d/box2d.h>)
#define USING_BOX2D
#include <box2d/box2d.h>
#endif
