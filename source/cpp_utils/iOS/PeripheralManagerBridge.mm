////
////  PeripheralManagerBridge.h
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
//#include "Log.hpp"
//#include "PeripheralManagerBridge.h"
//
//
//#define NOTIFY_MTU      20
//
//#define TRANSFER_SERVICE_UUID           @"E20A39F4-73F5-4BC4-A12F-17D1AD07A961"
//#define TRANSFER_CHARACTERISTIC_UUID    @"08590F7E-DB05-467E-8757-72F6FAEB13D4"
//
//
//@interface PeripheralManagerBridge () <CBPeripheralManagerDelegate>
//
//@property (strong, nonatomic) CBPeripheralManager       *peripheralManager;
//@property (strong, nonatomic) CBMutableCharacteristic   *transferCharacteristic;
//@property (strong, nonatomic) NSData                    *dataToSend;
//@property (nonatomic, readwrite) NSInteger              sendDataIndex;
//
//@end
//
//
//
//#define NOTIFY_MTU      20
//
//
//
//@implementation PeripheralManagerBridge
//
//
//
//#pragma mark - View Lifecycle
//
//+ (void)setup {
//    Log << "Setup";
//    static PeripheralManagerBridge* instance = nil;
//    instance = [[PeripheralManagerBridge alloc] init];
//}
//
//- (instancetype)init {
//    // Start up the CBPeripheralManager
//    Log << "Init";
//    _peripheralManager = [[CBPeripheralManager alloc] initWithDelegate:self queue:nil];
//    return self;
//}
//
//#pragma mark - Peripheral Methods
//
//
///** Required protocol method.  A full app should take care of all the possible states,
// *  but we're just waiting for  to know when the CBPeripheralManager is ready
// */
//- (void)peripheralManagerDidUpdateState:(CBPeripheralManager *)peripheral
//{
//    // Opt out from any other state
//    if (peripheral.state != CBManagerStatePoweredOn) {
//        return;
//    }
//
//    // We're in CBPeripheralManagerStatePoweredOn state...
//    Log << @"self.peripheralManager powered on.";
//
//    // ... so build our service.
//
//    // Start with the CBMutableCharacteristic
//    self.transferCharacteristic = [[CBMutableCharacteristic alloc] initWithType:[CBUUID UUIDWithString:TRANSFER_CHARACTERISTIC_UUID]
//                                                                      properties:CBCharacteristicPropertyNotify
//                                                                           value:nil
//                                                                     permissions:CBAttributePermissionsReadable];
//
//    // Then the service
//    CBMutableService *transferService = [[CBMutableService alloc] initWithType:[CBUUID UUIDWithString:TRANSFER_SERVICE_UUID]
//                                                                        primary:YES];
//
//    // Add the characteristic to the service
//    transferService.characteristics = @[self.transferCharacteristic];
//
//    // And add it to the peripheral manager
//    [self.peripheralManager addService:transferService];
//}
//
//
///** Catch when someone subscribes to our characteristic, then start sending them data
// */
//- (void)peripheralManager:(CBPeripheralManager *)peripheral central:(CBCentral *)central didSubscribeToCharacteristic:(CBCharacteristic *)characteristic
//{
//    Log << @"Central subscribed to characteristic";
//
//
//    static int a = 0;
//
//    NSString* datovka = [NSString stringWithFormat:@"Dativko: %d", a++];
//
//    // Get the data
//    self.dataToSend = [datovka dataUsingEncoding:NSUTF8StringEncoding];
//
//    // Reset the index
//    self.sendDataIndex = 0;
//
//    // Start sending
//    [self sendData];
//}
//
//
///** Recognise when the central unsubscribes
// */
//- (void)peripheralManager:(CBPeripheralManager *)peripheral central:(CBCentral *)central didUnsubscribeFromCharacteristic:(CBCharacteristic *)characteristic
//{
//    Log << @"Central unsubscribed from characteristic";
//}
//
//
//- (void)peripheralManager:(CBPeripheralManager *)peripheral didAddService:(CBService *)service error:(NSError *)error {
//
//    Logvar([error localizedDescription]);
//
//    [self startAdv:true];
//
//}
//
///** Sends the next amount of data to the connected central
// */
//- (void)sendData
//{
//    // First up, check if we're meant to be sending an EOM
//    static BOOL sendingEOM = NO;
//
//    if (sendingEOM) {
//
//        // send it
//        BOOL didSend = [self.peripheralManager updateValue:[@"EOM" dataUsingEncoding:NSUTF8StringEncoding] forCharacteristic:self.transferCharacteristic onSubscribedCentrals:nil];
//
//        // Did it send?
//        if (didSend) {
//
//            // It did, so mark it as sent
//            sendingEOM = NO;
//
//            Log << @"Sent: EOM";
//        }
//
//        // It didn't send, so we'll exit and wait for peripheralManagerIsReadyToUpdateSubscribers to call sendData again
//        return;
//    }
//
//    // We're not sending an EOM, so we're sending data
//
//    // Is there any left to send?
//
//    if (self.sendDataIndex >= self.dataToSend.length) {
//
//        // No data left.  Do nothing
//        return;
//    }
//
//    // There's data left, so send until the callback fails, or we're done.
//
//    BOOL didSend = YES;
//
//    while (didSend) {
//
//        // Make the next chunk
//
//        // Work out how big it should be
//        NSInteger amountToSend = self.dataToSend.length - self.sendDataIndex;
//
//        // Can't be longer than 20 bytes
//        if (amountToSend > NOTIFY_MTU) amountToSend = NOTIFY_MTU;
//
//        // Copy out the data we want
//        NSData *chunk = [NSData dataWithBytes:(char*)self.dataToSend.bytes+self.sendDataIndex length:amountToSend];
//
//        // Send it
//        didSend = [self.peripheralManager updateValue:chunk forCharacteristic:self.transferCharacteristic onSubscribedCentrals:nil];
//
//        // If it didn't work, drop out and wait for the callback
//        if (!didSend) {
//            return;
//        }
//
//        NSString *stringFromData = [[NSString alloc] initWithData:chunk encoding:NSUTF8StringEncoding];
//        Logvar(stringFromData);
//
//        // It did send, so update our index
//        self.sendDataIndex += amountToSend;
//
//        // Was it the last one?
//        if (self.sendDataIndex >= self.dataToSend.length) {
//
//            // It was - send an EOM
//
//            // Set this so if the send fails, we'll send it next time
//            sendingEOM = YES;
//
//            // Send it
//            BOOL eomSent = [self.peripheralManager updateValue:[@"EOM" dataUsingEncoding:NSUTF8StringEncoding] forCharacteristic:self.transferCharacteristic onSubscribedCentrals:nil];
//
//            if (eomSent) {
//                // It sent, we're all done
//                sendingEOM = NO;
//
//                Log << @"Sent: EOM";
//            }
//
//            return;
//        }
//    }
//}
//
//
///** This callback comes in when the PeripheralManager is ready to send the next chunk of data.
// *  This is to ensure that packets will arrive in the order they are sent
// */
//- (void)peripheralManagerIsReadyToUpdateSubscribers:(CBPeripheralManager *)peripheral
//{
//    Log;
//    // Start sending again
//    [self sendData];
//}
//
//
//#pragma mark - TextView Methods
//
//
///** Start advertising
// */
//- (void)startAdv:(BOOL)start
//{
//    Logvar(start);
//
//    if (start) {
//          NSDictionary *advertisingData =
//        @{CBAdvertisementDataLocalNameKey : @"Test3", CBAdvertisementDataServiceUUIDsKey : @[[CBUUID UUIDWithString:TRANSFER_SERVICE_UUID]]};
//
//        [self.peripheralManager startAdvertising:advertisingData];
//    }
//
//    else {
//        [self.peripheralManager stopAdvertising];
//    }
//}
//
//
//@end
//
//#endif
