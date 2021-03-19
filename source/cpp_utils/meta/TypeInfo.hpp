//
//  TypeInfo.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 18/03/2021.
//  Copyright © 2021 VladasZ. All rights reserved.
//

#pragma once

#include <type_traits>

#include "LogUtils.hpp"


namespace cu {

	template <class T>
	struct TypeInfo {

		using Type = T;

		static constexpr bool is_ref     = std::is_reference_v<Type>;
		static constexpr bool is_const   = std::is_const_v<std::remove_reference_t<Type>>;
		static constexpr bool is_pointer = std::is_pointer_v<std::remove_reference_t<Type>>;

		static constexpr bool is_const_ref = is_const && is_ref;

		static std::string to_string() {
			return "\n" +
				VarString(is_ref)       + "\n" +
				VarString(is_const)     + "\n" +
				VarString(is_pointer)   + "\n" +
				VarString(is_const_ref) + "\n";
		}

	};

}
