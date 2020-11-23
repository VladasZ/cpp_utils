//
//  CallObj.c
//  TestEngine
//
//  Created by Vladas Zakrevskis on 8/19/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#ifdef __OBJC__

#ifdef IOS_BUILD
#import <UIKit/UIKit.h>
#else
#import <AppKit/AppKit.h>
#endif

#include "Log.hpp"
#include "CallObj.hpp"

using namespace std;
using namespace obj_c;


#ifdef IOS_BUILD
static UIViewController *topmostController() {
    UIViewController *controller = [UIApplication sharedApplication].keyWindow.rootViewController;
    while (controller.presentedViewController != nil) {
        controller = controller.presentedViewController;
    }
    return controller;
}
#endif

#ifdef IOS_BUILD
ScreenInfo obj_c::screen_info() {
    ScreenInfo info;

    info.scale = (unsigned)[[UIScreen mainScreen] scale];

    CGRect bounds = [[UIScreen mainScreen] bounds];

    info.res_x = (float)(info.scale * bounds.size.width);
    info.res_y = (float)(info.scale * bounds.size.height);

    info.refresh_rate = (unsigned)[[UIScreen mainScreen] maximumFramesPerSecond];

    if (info.scale == 1) {
        info.ppi = 163;
    }
    else if (info.scale == 2) {
        info.ppi = 326;
    }
    else {
        info.ppi = 458;
    }

    return info;
}
#endif

std::string obj_c::work_directory_path() {
    return [[[NSBundle mainBundle] bundlePath] UTF8String];
}

void obj_c::show_alert(const string& message) {

    NSString *messageString = [NSString stringWithUTF8String:message.c_str()];

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

vector<string> obj_c::ls(const string& path) {

    NSArray<NSString*>* ns_ls = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:@(path.c_str()) error:nil];

    vector<string> result;
    for (NSString* file in ns_ls) {
        result.push_back([file UTF8String]);
    }
    return result;
}

#endif
