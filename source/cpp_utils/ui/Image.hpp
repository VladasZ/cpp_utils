//
//  Image.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 2/19/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include <cstdint>
#include <string>

class Image {

protected:

    void*   _data;
    float   _width;
    float   _height;
    uint8_t _channels;

public:

    explicit Image(const std::string& path);
    explicit Image(void* data, float width, float height, uint8_t channels);
    virtual ~Image();

    float       width()         const;
    float       height()        const;
    void*       data()          const;
    uint8_t     channels()      const;
    bool        is_monochrome() const;

protected:

    void _free_data();
};
