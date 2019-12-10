//
//  AndroidSystem.cpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 12/6/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#ifdef ANDROID_BUILD

#include "Log.hpp"
#include "AndroidSystem.hpp"
#include "ExceptionCatch.hpp"

void AndroidSystem::set_asset_manager(AAssetManager* manager) {
    if (manager == nullptr) {
        throw std::runtime_error("Failed to set asset manager.");
    }
    asset_manager = manager;
}

cu::File AndroidSystem::load_file(const std::string& path) {


    AAssetDir* assetDir = AAssetManager_openDir(asset_manager, "drawabled");

    Logvar(assetDir);

    AAsset* asset = nullptr;

    if (asset_manager == nullptr) {
        throw std::runtime_error("Asset manager is not set up.");
    }

    try {
        asset = AAssetManager_open(asset_manager, "ic_android_black_24dp.xml", AASSET_MODE_STREAMING);
    }
    catch (...) {
        auto error = what();
        throw std::runtime_error(error);
    }

    if (asset == nullptr) {
        throw std::runtime_error("Failed to open file: " + path);
    }
    int size = AAsset_getLength(asset);
    auto data = new char[size];
    int read = AAsset_read(asset, data, size);
    if (read != size) {
        throw std::runtime_error("Failed to read file: " + path);
    }
    AAsset_close(asset);
    return  { data, static_cast<unsigned>(size) };
}

#endif
