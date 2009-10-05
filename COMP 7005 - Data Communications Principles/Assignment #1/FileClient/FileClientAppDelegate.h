//
//  FileClientAppDelegate.h
//  FileClient
//
//  Created by Steffen L. Norgren on 09-10-05.
//  Copyright 2009 Esurient Systems Inc.. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface FileClientAppDelegate : NSObject <NSApplicationDelegate> {
    NSWindow *window;
}

@property (assign) IBOutlet NSWindow *window;

@end
