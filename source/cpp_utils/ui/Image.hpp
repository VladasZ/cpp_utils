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

public:

    struct Size {
        float width  = 0;
        float height = 0;
        Size() = default;
        Size(float, float);
    };

protected:

    void*   _data;
    Size    _size;
    uint8_t _channels;

public:

    explicit Image(const std::string& path);
    explicit Image(void* data, const Size& size, uint8_t channels);
    virtual ~Image();

    void*       data()          const;
    uint8_t     channels()      const;
    bool        is_monochrome() const;

protected:

    void _free_data();
};
