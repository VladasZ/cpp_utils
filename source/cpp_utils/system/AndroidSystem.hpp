//
//  AndroidSystem.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 12/6/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#ifdef ANDROID_BUILD

#include <string>

#include <android/asset_manager.h>

class AndroidSystem {

	static inline AAssetManager* asset_manager = nullptr;

public:

    using FileData = std::pair<char*, unsigned>;

	static void set_asset_manager(AAssetManager*);

	static FileData load_file(const std::string& path);

	static void log(const std::string&);

};

#endif
