//
//  AndroidSystem.cpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 12/6/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#ifdef ANDROID_BUILD

#include <android/log.h>

#include "Log.hpp"
#include "AndroidSystem.hpp"
#include "ExceptionCatch.hpp"

void AndroidSystem::set_asset_manager(AAssetManager* manager) {
    if (manager == nullptr) {
        Fatal("Failed to set asset manager. Manager is nullptr.");
    }
    asset_manager = manager;
}

AndroidSystem::FileData AndroidSystem::load_file(const std::string& path) {

    if (asset_manager == nullptr) {
        Fatal("Asset manager is not set up.");
    }

    auto asset = AAssetManager_open(asset_manager, path.c_str(), AASSET_MODE_STREAMING);

    if (asset == nullptr) {
        Fatal("Failed to open file: " + path);
    }

    int size = AAsset_getLength(asset);
    auto data = new char[size];
    int read = AAsset_read(asset, data, size);

    if (read != size) {
        Fatal("Failed to read file: " + path);
    }

    AAsset_close(asset);
    return  { data, static_cast<unsigned>(size) };
}

void AndroidSystem::log(const std::string& message) {
    __android_log_print(ANDROID_LOG_INFO, "cu::Log", "%s", message.c_str());
}

#endif
