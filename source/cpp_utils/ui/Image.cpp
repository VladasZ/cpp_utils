//
//  Image.cpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 2/19/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#include "SOIL.h"

#include "Image.hpp"

Image::Size::Size(float width, float height) : width(width), height(height) {

}

Image::Image(const std::string& path) {

    int width;
    int height;
    int channels;

    _data = SOIL_load_image(path.c_str(),
                            &width,
                            &height,
                            &channels,
                            SOIL_LOAD_RGBA);

    if (_data == nullptr)
        throw std::string() + "Failed to load image: " + path;

    _size     = { static_cast<float>(width), static_cast<float>(height) };
    _channels = static_cast<uint8_t>(channels);
}

Image::Image(void* data, const Size& size, uint8_t channels) : _data(data), _size(size),  _channels(channels) {

}

Image::~Image() {
    _free_data();
}

void* Image::data() const {
    return _data;
}

uint8_t Image::channels() const {
    return _channels;
}

bool Image::is_monochrome() const {
    return _channels == 1;
}

void Image::_free_data() {
    if (_data) {
        free(_data);
        _data = nullptr;
    }
}
