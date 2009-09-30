//
//  Encrypted_ChatAppDelegate.h
//  Encrypted Chat
//
//  Created by Steffen L. Norgren on 09-09-29.
//  Copyright 2009 Esurient Systems Inc.. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface Encrypted_ChatAppDelegate : NSObject <NSApplicationDelegate> {
    NSWindow *window;

	BOOL isRunning;
	
	// Main Window
    IBOutlet id logView;
	IBOutlet id encryptCheck;
    IBOutlet id connectListenButton;
	IBOutlet id inputView;
	
	// Preferences Window: Connection
	IBOutlet id remoteIP;
	IBOutlet id displayName;
	IBOutlet id clientMode;
	IBOutlet id serverMode;

	// Preferences Window: Encryption
	IBOutlet id cipherVigenere;
	IBOutlet id cipherAffine;
	IBOutlet id vigenereMult;
	IBOutlet id vigenereAdd;
	IBOutlet id affineKey;
}

@property (assign) IBOutlet NSWindow *window;

@end
