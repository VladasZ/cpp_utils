//
//  CircularBuffer.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 05/03/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#include <array>
#include <string>


namespace cu {

    template<size_t size>
    class CircularBuffer {

    private:

        unsigned _current_index = 0;
        std::array<uint8_t, size> _data = { 0 };

    private:

        size_t _distance_to_end() const {
            return size - _current_index;
        }

    public:

        void add_byte(uint8_t byte) {
            _data[_current_index] = byte;
            if (_current_index == size - 1) {
                _current_index = 0;
            }
            else {
                _current_index++;
            }
        }

        template<class Value>
        void add(const Value& val) {
            add(&val, sizeof(val));
        }

        void add(const void* data, size_t _size) {
            if (_current_index + _size < size) {
                memcpy(_data.data() + _current_index, data, _size);
                _current_index += _size;
                return;
            }
            auto first_part_size = _distance_to_end();
            auto second_part_size = _size - first_part_size;

            memcpy(_data.data() + _current_index, data, first_part_size);
            memcpy(_data.data(), static_cast<const uint8_t*>(data) + first_part_size, second_part_size);

            _current_index = second_part_size;
        }

        template<class Value>
        void get(Value& val) const {
            static constexpr auto _size = sizeof(Value);
            auto dst = reinterpret_cast<uint8_t*>(&val);
            if (_current_index >= _size) {
                memcpy(dst, _data.data() + _current_index - _size, _size);
                return;
            }

            auto first_part_size = _size - _current_index;
            auto second_part_size = _current_index;

            memcpy(dst, _data.data() + size - first_part_size, first_part_size);
            memcpy(dst + first_part_size, _data.data(), second_part_size);

        }

        std::string dump() const {
            std::string result;
            for (auto& byte : _data) {
                result += std::to_string((int)byte) + " ";
            }
            result.pop_back();
            return result;
        }

    };

}
