//
//  MacGPGFileToolAppDelegate.h
//  MacGPGFileTool
//
//  Created by Steffen L. Norgren on 09-11-10.
//  Copyright 2009 Esurient Systems Inc.. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface MacGPGFileToolAppDelegate : NSObject <NSApplicationDelegate> {
    NSWindow *window;
}

@property (assign) IBOutlet NSWindow *window;

@end
