//
//  MacGPGToolAppDelegate.h
//  MacGPGTool
//
//  Created by Steffen L. Norgren on 09-12-08.
//  Copyright 2009 Esurient Systems Inc.. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface MacGPGToolAppDelegate : NSObject <NSApplicationDelegate> {
    NSWindow *window;
}

@property (assign) IBOutlet NSWindow *window;

@end
