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

#include <jni.h>
#include <android/asset_manager.h>
#include <android/log.h>

#include "File.hpp"

class AndroidSystem {

	static inline AAssetManager* asset_manager = nullptr;

public:

	static void set_asset_manager(AAssetManager*);

	static cu::File load_file(const std::string& path);

};

#endif
