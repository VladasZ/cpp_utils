//
//  CentralManagerBridge.mm
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 24/03/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#import <CoreBluetooth/CoreBluetooth.h>

#import "Log.hpp"
#import "CentralManagerBridge.h"

static CBCentralManager* centralManager;
static CentralManagerBridge* instance;


@interface CentralManagerBridge () <CBCentralManagerDelegate>
@end

@implementation CentralManagerBridge


+ (void)testCentral {

    instance = [CentralManagerBridge new];

    dispatch_queue_t queue = dispatch_queue_create("bluetoothQueue",
                                                   DISPATCH_QUEUE_CONCURRENT);

    centralManager =
            [[CBCentralManager alloc] initWithDelegate:instance queue:queue options:nil];

}

- (void)centralManagerDidUpdateState:(CBCentralManager*)central {
    Logvar(central);
    if (central.state == CBManagerStatePoweredOn) {
        Log("Powered On");
        Log("[centralManager scanForPeripheralsWithServices:nil options:nil]");
        [centralManager scanForPeripheralsWithServices:nil options:nil];
    }
    Logvar(central.state);
}

- (void)centralManager:(CBCentralManager*)central connectionEventDidOccur:(CBConnectionEvent)event forPeripheral:(CBPeripheral*)peripheral {
    Log("connectionEventDidOccur");
}

- (void)centralManager:(CBCentralManager*)central didDisconnectPeripheral:(CBPeripheral*)peripheral error:(nullable NSError*)error {

}

- (void)centralManager:(CBCentralManager *)central didDiscoverPeripheral:(CBPeripheral *)peripheral advertisementData:(NSDictionary<NSString *, id> *)advertisementData RSSI:(NSNumber *)RSSI {
    Log("Discovered:");
    Log(peripheral.name);
    Log((long long)peripheral);
}

@end
