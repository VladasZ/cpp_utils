//
//  Bluetooth.cpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 02/02/20
//  Copyright © 2020 VladasZ. All rights reserved.
//

#ifdef APPLE
#include "CallObj.hpp"
#endif

#include "Bluetooth.hpp"

using namespace cu;

void Bluetooth::test() {
#ifdef APPLE
    obj_c::test_bluetooth();
#endif
}

