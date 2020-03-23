//
//  OBJBridge.h
//  TestEngine
//
//  Created by Vladas Zakrevskis on 8/19/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface OBJBridge : NSObject

+ (NSString*)workDirectoryPath;
+ (NSArray<NSString*>*)ls:(const char*)path;
+ (void)showAlert:(const char*)message;

@end
