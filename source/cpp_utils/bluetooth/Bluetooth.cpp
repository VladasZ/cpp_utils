//
//  Bluetooth.cpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 02/02/20
//  Copyright © 2020 VladasZ. All rights reserved.
//

#ifdef __APPLE__
#include "CallObj.hpp"
#endif

#include "Bluetooth.hpp"

using namespace cu;

void Bluetooth::test_central() {
#ifdef __APPLE__
    obj_c::test_central();
#endif
}

void Bluetooth::test_peripheral() {
#ifdef __APPLE__
    obj_c::test_peripheral();
#endif
}


