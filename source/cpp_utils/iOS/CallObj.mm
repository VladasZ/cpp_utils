//
//  CallObj.c
//  TestEngine
//
//  Created by Vladas Zakrevskis on 8/19/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#ifdef APPLE

#include "CallObj.hpp"
#include "OBJBridge.h"
#include "CentralManagerBridge.h"
#include "PeripheralManagerBridge.h"

using namespace std;
using namespace obj_c;

const string obj_c::work_directory_path = [[OBJBridge workDirectoryPath] UTF8String];

void obj_c::show_alert(const string& message) {
    [OBJBridge showAlert:message.c_str()];
}

vector<string> obj_c::ls(const string& path) {
    vector<string> result;
    for (NSString* file in [OBJBridge ls:path.c_str()]) {
        result.push_back([file UTF8String]);
    }
    return result;
}

void obj_c::test_central() {
    [CentralManagerBridge testCentral];
}

void obj_c::test_peripheral() {
    [PeripheralManagerBridge testPeripheral];
}

#endif
