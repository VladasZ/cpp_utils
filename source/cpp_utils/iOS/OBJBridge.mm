//
//  OBJBridge.m
//  TestEngine
//
//  Created by Vladas Zakrevskis on 8/19/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#ifdef __OBJC__

#include "Log.hpp"
#include "Target.hpp"

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


@interface OBJBridge () 
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

@end

#endif
