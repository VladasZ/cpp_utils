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


static CBPeripheralManager* perManager;
static CBCentralManager* centmanager;

static CBMutableCharacteristic *characteristic;
static CBMutableCharacteristic *characteristic1;
static CBMutableCharacteristic *characteristic2;
static CBMutableService *servicea;


@interface PeripheralManagerBridge () <CBPeripheralManagerDelegate, CBCentralManagerDelegate, CBPeripheralDelegate>
@end


@implementation PeripheralManagerBridge

+ (void)testPeripheral {
    
    perManager = [[CBPeripheralManager alloc] initWithDelegate:self queue:nil];
 //   centmanager = [[CBCentralManager alloc] initWithDelegate:self queue:nil];
    
    Log("Peripherol");
}

#pragma mark - CBPeripheralManagerDelegate


+ (void)peripheralManagerDidUpdateState:(CBPeripheralManager *)peripheral{
    NSLog(@"Done");
    switch (peripheral.state) {
        case CBPeripheralManagerStatePoweredOn:{
            CBUUID *cUDID = [CBUUID UUIDWithString:@"DA18"];
            CBUUID *cUDID1 = [CBUUID UUIDWithString:@"DA17"];
            CBUUID *cUDID2 = [CBUUID UUIDWithString:@"DA16"];
  
            

            CBUUID *sUDID = [CBUUID UUIDWithString:@"EBA38950-0D9B-4DBA-B0DF-BC7196DD44FC"];
            characteristic = [[CBMutableCharacteristic alloc]initWithType:cUDID properties:CBCharacteristicPropertyNotify value:nil permissions:CBAttributePermissionsReadable];
            characteristic1 = [[CBMutableCharacteristic alloc]initWithType:cUDID1 properties:CBCharacteristicPropertyWrite value:nil permissions:CBAttributePermissionsWriteable];
            characteristic2 = [[CBMutableCharacteristic alloc]initWithType:cUDID2 properties:CBCharacteristicPropertyRead value:nil permissions:CBAttributePermissionsReadable];
            NSLog(@"%u",characteristic2.properties);
            servicea = [[CBMutableService alloc]initWithType:sUDID primary:YES];
            servicea.characteristics = @[characteristic,characteristic1,characteristic2];
            [peripheral addService:servicea];
        }
            break;
            
        default:
            NSLog(@"%i",peripheral.state);
            break;
    }
    NSLog(@"%i",peripheral.state);

}

+ (void)peripheralManager:(CBPeripheralManager *)peripheral didAddService:(CBService *)service error:(NSError *)error{
    NSLog(@"Added");
    NSDictionary *advertisingData = @{CBAdvertisementDataLocalNameKey : @"Allaglieviiallagliec", CBAdvertisementDataServiceUUIDsKey : @[[CBUUID UUIDWithString:@"EBA38950-0D9B-4DBA-B0DF-BC7196DD44FC"]]};

    [peripheral startAdvertising:advertisingData];
}

+ (void)peripheralManagerDidStartAdvertising:(CBPeripheralManager *)peripheral error:(NSError *)error {
    Log("");
}

+ (void)peripheralManager:(CBPeripheralManager *)peripheral central:(CBCentral *)central didSubscribeToCharacteristic:(CBCharacteristic *)characteristic12{
    NSLog(@"Core:%@",characteristic12.UUID);
    NSLog(@"Connected");
  //  [self writeData:peripheral];
}


@end
