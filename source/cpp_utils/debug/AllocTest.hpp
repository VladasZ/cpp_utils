//
//  AllocTest.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 04/08/2020.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

#include "Log.hpp"



class AllocTest {

public:

	 AllocTest() { Log << "Alloc";   }
	~AllocTest() { Log << "Dealloc"; }

};
