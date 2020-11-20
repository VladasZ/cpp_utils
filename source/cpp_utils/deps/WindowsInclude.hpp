//
//  WindowsInclude.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 09/10/2020.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once


#ifdef _WIN32
	#ifndef _CRT_SECURE_NO_WARNINGS
		#define _CRT_SECURE_NO_WARNINGS
	#endif
	#include <windows.h>
#endif
