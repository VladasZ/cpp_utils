//
//  Bitwise.hpp
//  cpp_tools
//
//  Created by Vladas Zakrevskis on 11/15/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#pragma once

#include <string>
#include <type_traits>


namespace bitwise {

    template <class T>
    constexpr size_t size = sizeof(T) * 8;

    template <uint8_t bit_size, bool _signed = false>
    class fits {

        static_assert(bit_size <= 64);

        using  _8 = typename std::conditional<_signed,   int8_t,   uint8_t>::type;
        using _16 = typename std::conditional<_signed,  int16_t,  uint16_t>::type;
        using _32 = typename std::conditional<_signed,  int32_t,  uint32_t>::type;
        using _64 = typename std::conditional<_signed,  int64_t,  uint64_t>::type;

        static constexpr bool fits_8  = bit_size <=  8;
        static constexpr bool fits_16 = bit_size <= 16;
        static constexpr bool fits_32 = bit_size <= 32;

    public:

        using type = typename std::conditional<fits_8,   _8,
                     typename std::conditional<fits_16, _16,
                     typename std::conditional<fits_32, _32, _64>::type>::type>::type;

    };

    template <uint8_t bit_size, bool _signed = false>
    using fits_t = typename fits<bit_size, _signed>::type;

    template <class T>
    constexpr auto& to_number(const T& value) {
        return *static_cast<const fits_t<size<T>>*>(static_cast<const void*>(&value));
    }

    template <class T, class NumberType>
    constexpr auto& to_type(const NumberType& value) {
        return *static_cast<const T*>(static_cast<const void*>(&value));
    }

    constexpr auto flag(uint8_t index, bool value = true) {
        return static_cast<uint64_t>(value) << index;
    }

    template <class T>
    constexpr bool get_bit(uint8_t index, const T& value) {
        return static_cast<bool>(to_number(value) & flag(index));
    }

    template <class T>
    constexpr T set_bit(const T& value, uint8_t index, bool bit = true) {
        auto result = to_number(value);
        result &= ~flag(index);
        result |= flag(index, bit);
        return to_type<T>(result);
    }

    template <uint8_t begin, uint8_t end, class T>
    constexpr auto get_part(const T& value) {
        constexpr uint8_t span = end - begin + 1;
        fits_t<span> result { 0 };
        for (int i = 0; i < span; i++) {
            result = set_bit(result, i, get_bit(begin + i, value));
        }
        return result;
    }

    template <class T>
    static std::string to_string(const T& value) {
        static_assert(size<T> <= 64, "bitwise::to_string value is too big");
        std::string result;
        for (int i = size<T> - 1; i >= 0; i--) {
            result += std::to_string(get_bit(i, value));
            if (i % 8 == 0) {
                result += " ";
            }
        }
        return result;
    }
}
