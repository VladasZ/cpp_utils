//
//  FreeTypeInclude.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 11/09/2020.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#if __has_include(<ft2build.h>)
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
#define USING_FREETYPE
#endif
