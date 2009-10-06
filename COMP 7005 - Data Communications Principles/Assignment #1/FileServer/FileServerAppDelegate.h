/*-----------------------------------------------------------------------------
 * SOURCE FILE:	FileServerAppDelegate.h
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

@interface FileServerAppDelegate : NSObject <NSApplicationDelegate>
{
    NSWindow *window;
	
	Server *server;
//	Client *client;
	BOOL isRunning;
	
	NSMutableArray *dataConn;	// Contains all data connections
	
	// Main Window
    IBOutlet id logView;
	IBOutlet id listenButton;	
}

@property (assign) IBOutlet NSWindow *window;

- (void)initWindow;
- (void)dealloc;

- (IBAction)listenForConnect:(id)sender;
- (void)logMessage:(NSString *)msg logType:(NSString *)type;
- (void)sendFile:(NSString *)fileName toConnection:(Client *)con;

@end
