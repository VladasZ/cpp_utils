////
////  CentralManagerBridge.mm
////  cpp_utils
////
////  Created by Vladas Zakrevskis on 24/03/20.
////  Copyright © 2020 VladasZ. All rights reserved.
////
//
//#ifdef __OBJC__
//
//#import <CoreBluetooth/CoreBluetooth.h>
//
//#import "Log.hpp"
//#import "CentralManagerBridge.h"
//
//#define TRANSFER_SERVICE_UUID           @"E20A39F4-73F5-4BC4-A12F-17D1AD07A961"
//#define TRANSFER_CHARACTERISTIC_UUID    @"08590F7E-DB05-467E-8757-72F6FAEB13D4"
//
//
//@interface CentralManagerBridge () <CBCentralManagerDelegate, CBPeripheralDelegate>
//
//@property (strong, nonatomic) CBCentralManager      *centralManager;
//@property (strong, nonatomic) CBPeripheral          *discoveredPeripheral;
//@property (strong, nonatomic) NSMutableData         *data;
//
//@end
//
//
//
//@implementation CentralManagerBridge
//
//+ (void)testCentral {
//    static CentralManagerBridge* instance = nil;
//    instance = [[CentralManagerBridge alloc] init];
//}
//
//#pragma mark - View Lifecycle
//
//- (instancetype)init {
//    // Start up the CBCentralManager
//    Log;
//    _centralManager = [[CBCentralManager alloc] initWithDelegate:self queue:nil];
//
//    // And somewhere to store the incoming data
//    _data = [[NSMutableData alloc] init];
//
//    return self;
//}
//
//#pragma mark - Central Methods
//
//
//
///** centralManagerDidUpdateState is a required protocol method.
// *  Usually, you'd check for other states to make sure the current device supports LE, is powered on, etc.
// *  In this instance, we're just using it to wait for CBCentralManagerStatePoweredOn, which indicates
// *  the Central is ready to be used.
// */
//- (void)centralManagerDidUpdateState:(CBCentralManager *)central
//{
//
//    Log;
//
//    if (central.state != CBManagerStatePoweredOn) {
//        // In a real app, you'd deal with all the states correctly
//        return;
//    }
//
//    // The state must be CBCentralManagerStatePoweredOn...
//
//    // ... so start scanning
//    [self scan];
//
//}
//
//
///** Scan for peripherals - specifically for our service's 128bit CBUUID
// */
//- (void)scan
//{
//
////    [self.centralManager scanForPeripheralsWithServices:@[[CBUUID UUIDWithString:TRANSFER_SERVICE_UUID]]
////                                                options:@{ CBCentralManagerScanOptionAllowDuplicatesKey : @YES }];
//
//    [self.centralManager scanForPeripheralsWithServices:nil options:nil];
//
//    Log << @"Scanning started";
//}
//
//
///** This callback comes whenever a peripheral that is advertising the TRANSFER_SERVICE_UUID is discovered.
// *  We check the RSSI, to make sure it's close enough that we're interested in it, and if it is,
// *  we start the connection process
// */
//- (void)centralManager:(CBCentralManager *)central didDiscoverPeripheral:(CBPeripheral *)peripheral advertisementData:(NSDictionary *)advertisementData RSSI:(NSNumber *)RSSI
//{
//
//
//    // Ok, it's in range - have we already seen it?
//    if (self.discoveredPeripheral != peripheral) {
//
//        // Save a local copy of the peripheral, so CoreBluetooth doesn't get rid of it
//        self.discoveredPeripheral = peripheral;
//
//        Log << peripheral.name;
//
//        // And connect
//        Log << peripheral;
//       // [self.centralManager connectPeripheral:peripheral options:nil];
//    }
//}
//
//
///** If the connection fails for whatever reason, we need to deal with it.
// */
//- (void)centralManager:(CBCentralManager *)central didFailToConnectPeripheral:(CBPeripheral *)peripheral error:(NSError *)error
//{
//    Log << @"Failed to connect to:";
//    Logvar(peripheral);
//    Logvar([error localizedDescription]);
//    [self cleanup];
//}
//
//
///** We've connected to the peripheral, now we need to discover the services and characteristics to find the 'transfer' characteristic.
// */
//- (void)centralManager:(CBCentralManager *)central didConnectPeripheral:(CBPeripheral *)peripheral
//{
//    Log << @"Peripheral Connected";
//
//    // Stop scanning
//    [self.centralManager stopScan];
//    Log << @"Scanning stopped";
//
//    // Clear the data that we may already have
//    [self.data setLength:0];
//
//    // Make sure we get the discovery callbacks
//    peripheral.delegate = self;
//
//    // Search only for services that match our UUID
//    [peripheral discoverServices:@[[CBUUID UUIDWithString:TRANSFER_SERVICE_UUID]]];
//}
//
//
///** The Transfer Service was discovered
// */
//- (void)peripheral:(CBPeripheral *)peripheral didDiscoverServices:(NSError *)error
//{
//    if (error) {
//        Logvar([error localizedDescription]);
//        [self cleanup];
//        return;
//    }
//
//    // Discover the characteristic we want...
//
//    // Loop through the newly filled peripheral.services array, just in case there's more than one.
//    for (CBService *service in peripheral.services) {
//        [peripheral discoverCharacteristics:@[[CBUUID UUIDWithString:TRANSFER_CHARACTERISTIC_UUID]] forService:service];
//    }
//}
//
//
///** The Transfer characteristic was discovered.
// *  Once this has been found, we want to subscribe to it, which lets the peripheral know we want the data it contains
// */
//- (void)peripheral:(CBPeripheral *)peripheral didDiscoverCharacteristicsForService:(CBService *)service error:(NSError *)error
//{
//    // Deal with errors (if any)
//    if (error) {
//        Logvar([error localizedDescription]);
//        [self cleanup];
//        return;
//    }
//
//    // Again, we loop through the array, just in case.
//    for (CBCharacteristic *characteristic in service.characteristics) {
//
//        // And check if it's the right one
//        if ([characteristic.UUID isEqual:[CBUUID UUIDWithString:TRANSFER_CHARACTERISTIC_UUID]]) {
//
//            // If it is, subscribe to it
//            [peripheral setNotifyValue:YES forCharacteristic:characteristic];
//        }
//    }
//
//    // Once this is complete, we just need to wait for the data to come in.
//}
//
//
///** This callback lets us know more data has arrived via notification on the characteristic
// */
//- (void)peripheral:(CBPeripheral *)peripheral didUpdateValueForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error
//{
//    if (error) {
//        Logvar([error localizedDescription]);
//        return;
//    }
//
//    NSString *stringFromData = [[NSString alloc] initWithData:characteristic.value encoding:NSUTF8StringEncoding];
//
//    // Have we got everything we need?
//    if ([stringFromData isEqualToString:@"EOM"]) {
//
//        Log << "GOT DOTO!";
//        Logvar([[NSString alloc] initWithData:self.data encoding:NSUTF8StringEncoding]);
//
//        // Cancel our subscription to the characteristic
//        [peripheral setNotifyValue:NO forCharacteristic:characteristic];
//
//        // and disconnect from the peripehral
//        [self.centralManager cancelPeripheralConnection:peripheral];
//    }
//
//    // Otherwise, just add the data on to what we already have
//    [self.data appendData:characteristic.value];
//
//    // Log it
//    Logvar(stringFromData);
//}
//
//
///** The peripheral letting us know whether our subscribe/unsubscribe happened or not
// */
//- (void)peripheral:(CBPeripheral *)peripheral didUpdateNotificationStateForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error
//{
//    if (error) {
//        Logvar(error.localizedDescription);
//    }
//
//    // Exit if it's not the transfer characteristic
//    if (![characteristic.UUID isEqual:[CBUUID UUIDWithString:TRANSFER_CHARACTERISTIC_UUID]]) {
//        return;
//    }
//
//    // Notification has started
//    if (characteristic.isNotifying) {
//        Logvar(characteristic);
//    }
//
//    // Notification has stopped
//    else {
//        // so disconnect from the peripheral
//        Logvar(characteristic);
//        [self.centralManager cancelPeripheralConnection:peripheral];
//    }
//}
//
//
///** Once the disconnection happens, we need to clean up our local copy of the peripheral
// */
//- (void)centralManager:(CBCentralManager *)central didDisconnectPeripheral:(CBPeripheral *)peripheral error:(NSError *)error
//{
//    Logvar(@"Peripheral Disconnected");
//    self.discoveredPeripheral = nil;
//
//    // We're disconnected, so start scanning again
//    [self scan];
//}
//
//
///** Call this when things either go wrong, or you're done with the connection.
// *  This cancels any subscriptions if there are any, or straight disconnects if not.
// *  (didUpdateNotificationStateForCharacteristic will cancel the connection if a subscription is involved)
// */
//- (void)cleanup
//{
//    // Don't do anything if we're not connected
//    if (!([self.discoveredPeripheral state] == CBPeripheralStateConnected)) {
//        return;
//    }
//
//    // See if we are subscribed to a characteristic on the peripheral
//    if (self.discoveredPeripheral.services != nil) {
//        for (CBService *service in self.discoveredPeripheral.services) {
//            if (service.characteristics != nil) {
//                for (CBCharacteristic *characteristic in service.characteristics) {
//                    if ([characteristic.UUID isEqual:[CBUUID UUIDWithString:TRANSFER_CHARACTERISTIC_UUID]]) {
//                        if (characteristic.isNotifying) {
//                            // It is notifying, so unsubscribe
//                            [self.discoveredPeripheral setNotifyValue:NO forCharacteristic:characteristic];
//
//                            // And we're done.
//                            return;
//                        }
//                    }
//                }
//            }
//        }
//    }
//
//    // If we've got this far, we're connected, but we're not subscribed, so we just disconnect
//    [self.centralManager cancelPeripheralConnection:self.discoveredPeripheral];
//}
//
//
//@end
//
//#endif
