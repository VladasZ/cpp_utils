//
//  PeripheralManagerBridge.h
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 24/03/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#import <CoreBluetooth/CoreBluetooth.h>

#include "Log.hpp"
#include "PeripheralManagerBridge.h"


#define NOTIFY_MTU      20

#define TRANSFER_SERVICE_UUID           @"E20A39F4-73F5-4BC4-A12F-17D1AD07A961"
#define TRANSFER_CHARACTERISTIC_UUID    @"08590F7E-DB05-467E-8757-72F6FAEB13D4"


@interface PeripheralManagerBridge () <CBPeripheralManagerDelegate>

@property (strong, nonatomic) CBPeripheralManager       *peripheralManager;
@property (strong, nonatomic) CBMutableCharacteristic   *transferCharacteristic;
@property (strong, nonatomic) NSData                    *dataToSend;
@property (nonatomic, readwrite) NSInteger              sendDataIndex;

@end


@implementation PeripheralManagerBridge

+ (void)setup {
    static PeripheralManagerBridge* instance = [[PeripheralManagerBridge alloc] init];
}

- (void)dealloc {
    Log("Dealloc");
}

- (instancetype)init {
    Log("init");
    _peripheralManager = [[CBPeripheralManager alloc] initWithDelegate:self queue:nil];
    return self;
}

- (void)startAdvertising {
    Log("startAdvertising");
    [_peripheralManager startAdvertising:@{ CBAdvertisementDataServiceUUIDsKey : @[[CBUUID UUIDWithString:TRANSFER_SERVICE_UUID]] }];
}

/** Required protocol method.  A full app should take care of all the possible states,
 *  but we're just waiting for  to know when the CBPeripheralManager is ready
 */
- (void)peripheralManagerDidUpdateState:(CBPeripheralManager *)peripheral
{
    // Opt out from any other state
    if (peripheral.state != CBManagerStatePoweredOn) {
        Log();
        return;
    }
    
    // We're in CBPeripheralManagerStatePoweredOn state...
    Log(@"self.peripheralManager powered on.");
    
    // ... so build our service.
    
    // Start with the CBMutableCharacteristic
    _transferCharacteristic = [[CBMutableCharacteristic alloc] initWithType:[CBUUID UUIDWithString:TRANSFER_CHARACTERISTIC_UUID]
                                                                      properties:CBCharacteristicPropertyNotify
                                                                           value:nil
                                                                     permissions:CBAttributePermissionsReadable];

    // Then the service
    CBMutableService *transferService = [[CBMutableService alloc] initWithType:[CBUUID UUIDWithString:TRANSFER_SERVICE_UUID]
                                                                        primary:YES];
    
    // Add the characteristic to the service
    transferService.characteristics = @[_transferCharacteristic];
    
    // And add it to the peripheral manager
    [_peripheralManager addService:transferService];
}

- (void)peripheralManager:(CBPeripheralManager *)peripheral central:(CBCentral *)central didSubscribeToCharacteristic:(CBCharacteristic *)characteristic
{
    Log(@"Central subscribed to characteristic");
    
    // Get the data
    self.dataToSend = [@"datnoje datovko!" dataUsingEncoding:NSUTF8StringEncoding];
    
    // Reset the index
    self.sendDataIndex = 0;
    
    // Start sending
    [self sendData];
}


/** Recognise when the central unsubscribes
 */
- (void)peripheralManager:(CBPeripheralManager *)peripheral central:(CBCentral *)central didUnsubscribeFromCharacteristic:(CBCharacteristic *)characteristic
{
    Log(@"Central unsubscribed from characteristic");
}

- (void)peripheralManagerIsReadyToUpdateSubscribers:(CBPeripheralManager *)peripheral
{
    Log();
    // Start sending again
    [self sendData];
}

/** Sends the next amount of data to the connected central
 */
- (void)sendData
{
    // First up, check if we're meant to be sending an EOM
    static BOOL sendingEOM = NO;
    
    if (sendingEOM) {
        
        // send it
        BOOL didSend = [_peripheralManager updateValue:[@"EOM" dataUsingEncoding:NSUTF8StringEncoding] forCharacteristic:_transferCharacteristic onSubscribedCentrals:nil];
        
        // Did it send?
        if (didSend) {
            
            // It did, so mark it as sent
            sendingEOM = NO;
            
            Log(@"Sent: EOM");
        }
        
        // It didn't send, so we'll exit and wait for peripheralManagerIsReadyToUpdateSubscribers to call sendData again
        return;
    }
    
    // We're not sending an EOM, so we're sending data
    
    // Is there any left to send?
    
    if (self.sendDataIndex >= self.dataToSend.length) {
        
        // No data left.  Do nothing
        return;
    }
    
    // There's data left, so send until the callback fails, or we're done.
    
    BOOL didSend = YES;
    
    while (didSend) {
        
        // Make the next chunk
        
        // Work out how big it should be
        NSInteger amountToSend = self.dataToSend.length - self.sendDataIndex;
        
        // Can't be longer than 20 bytes
        if (amountToSend > NOTIFY_MTU) amountToSend = NOTIFY_MTU;
        
        // Copy out the data we want
        NSData *chunk = [NSData dataWithBytes: (char*)self.dataToSend.bytes + self.sendDataIndex length:amountToSend];
        
        // Send it
        didSend = [_peripheralManager updateValue:chunk forCharacteristic:_transferCharacteristic onSubscribedCentrals:nil];
        
        // If it didn't work, drop out and wait for the callback
        if (!didSend) {
            return;
        }
        
        NSString *stringFromData = [[NSString alloc] initWithData:chunk encoding:NSUTF8StringEncoding];
        Log(stringFromData);
        
        // It did send, so update our index
        self.sendDataIndex += amountToSend;
        
        // Was it the last one?
        if (self.sendDataIndex >= self.dataToSend.length) {
            
            // It was - send an EOM
            
            // Set this so if the send fails, we'll send it next time
            sendingEOM = YES;
            
            // Send it
            BOOL eomSent = [_peripheralManager updateValue:[@"EOM" dataUsingEncoding:NSUTF8StringEncoding] forCharacteristic:_transferCharacteristic onSubscribedCentrals:nil];
            
            if (eomSent) {
                // It sent, we're all done
                sendingEOM = NO;
                
                Log(@"Sent: EOM");
            }
            
            return;
        }
    }
}

- (void)peripheralManager:(CBPeripheralManager *)peripheral didAddService:(CBService *)service error:(NSError *)error{
    Log(@"didAddService");
    NSDictionary *advertisingData =
  @{CBAdvertisementDataLocalNameKey : @"Test2", CBAdvertisementDataServiceUUIDsKey : @[[CBUUID UUIDWithString:TRANSFER_SERVICE_UUID]]};

    [peripheral startAdvertising:advertisingData];
}


@end
