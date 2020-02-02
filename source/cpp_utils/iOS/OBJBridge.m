//
//  OBJBridge.m
//  TestEngine
//
//  Created by Vladas Zakrevskis on 8/19/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#import "OBJBridge.h"

#ifdef IOS_BUILD

#import <UIKit/UIKit.h>

static UIViewController *topmostController() {
    UIViewController *controller = [UIApplication sharedApplication].keyWindow.rootViewController;
    while (controller.presentedViewController != nil) {
        controller = controller.presentedViewController;
    }
    return controller;
}

#else

#import <AppKit/AppKit.h>

#endif

#import <CoreBluetooth/CoreBluetooth.h>

static CBCentralManager* centralManager;
static OBJBridge* instance;


@interface OBJBridge () <CBCentralManagerDelegate>
@end

@implementation OBJBridge

+ (NSString*) workDirectoryPath {
    return [[NSBundle mainBundle] bundlePath];
}

+ (NSArray<NSString*>*)ls:(const char*)path {
    return [[NSFileManager defaultManager] contentsOfDirectoryAtPath:@(path) error:nil];
}

+ (void)showAlert:(const char *)message {
    
    NSString *messageString = [NSString stringWithUTF8String:message];
    
#ifdef IOS_BUILD
        
    UIAlertController *controller =
    [UIAlertController alertControllerWithTitle:nil
                                        message:messageString
                                 preferredStyle:UIAlertControllerStyleAlert];
    
    [controller addAction:[UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        
    }]];
    
    [topmostController() presentViewController:controller animated:YES completion:nil];
    
#else
    
    NSAlert *alert = [NSAlert new];
    [alert addButtonWithTitle:@"OK"];
    alert.messageText = messageString;
    [alert runModal];
    [alert release];

#endif

}

+ (void)testBluetooth {

    instance = [OBJBridge new];

    dispatch_queue_t queue = dispatch_queue_create("downLoadAGroupPhoto",
                                                   DISPATCH_QUEUE_CONCURRENT);

    centralManager =
            [[CBCentralManager alloc] initWithDelegate:instance queue:queue options:nil];

    [centralManager scanForPeripheralsWithServices:nil options:nil];


    NSLog(@"Hellof");
}


- (void)centralManagerDidUpdateState:(CBCentralManager*)central {
    NSLog(@"@%", central);
}

- (void)centralManager:(CBCentralManager*)central didDiscoverPeripheral:(CBPeripheral*)peripheral advertisementData:(NSDictionary<NSString*, id>*)advertisementData RSSI:(NSNumber*)RSSI {
    NSLog(@"Discovered %@", peripheral.name);
}

@end
