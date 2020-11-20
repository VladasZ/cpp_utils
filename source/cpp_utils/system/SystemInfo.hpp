//
//  SystemInfo.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 8/19/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#pragma once

#include "Target.hpp"


namespace cu {

	class SystemInfo {

	public:

		static inline constexpr bool is_desktop =
#ifdef DESKTOP_BUILD
			true;
#else
			false;
#endif

		static inline constexpr bool is_ios =
#ifdef IOS_BUILD
			true;
#else
			false;
#endif

		static inline constexpr bool is_android =
#ifdef ANDROID_BUILD
			true;
#else
			false;
#endif

		static inline constexpr bool is_mobile = is_ios || is_android;

	};

}
