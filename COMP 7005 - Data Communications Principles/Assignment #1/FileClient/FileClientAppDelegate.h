/*-----------------------------------------------------------------------------
 * SOURCE FILE:	FileClientAppDelegate.h
 * 
 * PROGRAM:     FileServer
 * 
 * DATE:        October 5, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * NOTES: This is the header file for the application's main delegate.
 *
 *---------------------------------------------------------------------------*/

#import <Cocoa/Cocoa.h>
#import "ClientServer.h"

@interface FileClientAppDelegate : NSObject <NSApplicationDelegate> {
    NSWindow *window;
	
	Server *server;
	Client *client;
	BOOL isRunning;
	
	NSString *basePath;	
	NSString *saveFile;
	
	// Main Window
    IBOutlet id logView;
	IBOutlet id commandText;
	IBOutlet id serverIP;
	IBOutlet id sendButton;
	IBOutlet id connectButton;
}

@property (assign) IBOutlet NSWindow *window;

- (void)initWindow;
- (void)dealloc;

- (IBAction)connect:(id)sender;
- (IBAction)sendCommand:(id)sender;
- (void)logMessage:(NSString *)msg logType:(NSString *)type;

@end
