//
//  Property.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 8/28/2019.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include <string>

namespace mapping {

	enum class PropertyType {
		None,
		Secure,
		Unique
	};

	template<
		class Class, 
		class _Member,
		PropertyType type
	>
	class Property {
	public:

		using Member = std::remove_const_t<_Member>;

		using Pointer = _Member Class::*;

		constexpr static bool is_string  = std::is_same_v<Member, std::string>;
		constexpr static bool is_float   = std::is_same_v<Member, int        >;
		constexpr static bool is_integer = std::is_same_v<Member, float      >;

		constexpr static bool is_secure  = type == PropertyType::Secure;
		constexpr static bool is_unique  = type == PropertyType::Unique;

		static_assert(is_string || is_float || is_integer, "Invalid property type");

		const std::string class_name = Class::class_name();
		const std::string member_name = database_type_name();

		const std::string name;
		const Pointer pointer;

		constexpr Property(const std::string& name, Pointer pointer) :
			name(name), pointer(pointer) {
		}

		std::string database_type_name() const {
			if constexpr (is_string) {
				return "TEXT";
			}
			else if constexpr (is_float) {
				return "REAL";
			}
			else if constexpr (is_integer) {
				return "INTEGER";
			}
			else {
				throw std::runtime_error(std::string() +
					"Invalid member type: " + typeid(Member).name());
			}
		}

		std::string to_string() const {
			return std::string() +
				"Property: " + name + " of: " + class_name + " type: " + member_name;
		}

	};

}

#define PROPERTY(name)        mapping::Property<This, decltype(name), mapping::PropertyType::None   >(#name, &This::name)
#define SECURE_PROPERTY(name) mapping::Property<This, decltype(name), mapping::PropertyType::Secure >(#name, &This::name)
#define UNIQUE_PROPERTY(name) mapping::Property<This, decltype(name), mapping::PropertyType::Unique >(#name, &This::name)
