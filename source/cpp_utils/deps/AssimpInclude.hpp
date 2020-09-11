//
//  AssimpInclude.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 11/09/2020.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#if __has_include(<assimp/scene.h>)
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#define USING_ASSIMP
#endif
