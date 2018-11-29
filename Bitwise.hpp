//
//  Bitwise.hpp
//  cpp_tools
//
//  Created by Vladas Zakrevskis on 11/15/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//


#include <type_traits>
#include <string>


namespace bitwise {

	template <class T>
	constexpr size_t size = sizeof(T) * 8;

	template <uint8_t bit_size, bool _signed = false>
	using fits = typename std::conditional<bit_size <=  8, typename std::conditional<_signed,  int8_t,  uint8_t>::type,
		         typename std::conditional<bit_size <= 16, typename std::conditional<_signed, int16_t, uint16_t>::type,
		         typename std::conditional<bit_size <= 32, typename std::conditional<_signed, int32_t, uint32_t>::type,
		                                                   typename std::conditional<_signed, int64_t, uint64_t>::type>::type>::type>::type;

	template <class T>
	constexpr auto& to_number(const T& value) { 
		return *static_cast<const fits<size<T>>*>(static_cast<const void*>(&value)); 
	};

	template <class T, class NumberType>
	constexpr auto& to_type(const NumberType& value) {
		return *static_cast<const T*>(static_cast<const void*>(&value));
	}

	constexpr auto flag(uint8_t index, bool value = 1) {
		return static_cast<uint64_t>(value) << index;
	}

	template <class T>
	constexpr bool get_byte(uint8_t index, const T& value) {
		return static_cast<bool>(to_number(value) & flag(index));
	}

	template <class T>
	constexpr T set_byte(const T& value, uint8_t index, bool byte = 1) {
		auto result = to_number(value);
		result &= ~flag(index);
		result |= flag(index, byte);
		return to_type<T>(result);
	}

	template <uint8_t begin, uint8_t end, uint8_t span = end - begin, class T>
	constexpr auto get_part(const T& value) {
		fits<span> result(0);
		for (int i = 0; i < span; i++) 
			result = set_byte(result, i, get_byte(begin + i, value));
		return result;
	}

	template <class T>
	std::string to_string(const T& value) {
		static_assert(size<T> <= 64, "bitwise::to_string value is too big");
		std::string result;
		for (int i = size<T> - 1; i >= 0; i--) {
			result += std::to_string(get_byte(i, value));
			if (i % 8 == 0)
				result += " ";
		}
		return result;
	}
}
