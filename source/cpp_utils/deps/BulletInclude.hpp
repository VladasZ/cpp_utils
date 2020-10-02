//
//  BulletInclude.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 02/10/2020.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#if __has_include("btBulletDynamicsCommon.h")
#define USING_BULLET3D
#include "btBulletDynamicsCommon.h"
#endif
