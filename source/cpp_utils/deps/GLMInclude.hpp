//
//  GLMInclude.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 11/09/2020.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#if __has_include(<glm/gtc/quaternion.hpp>)
#define USING_GLM
#ifdef _WIN32
#pragma warning(disable : 4201)
#endif
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#endif
