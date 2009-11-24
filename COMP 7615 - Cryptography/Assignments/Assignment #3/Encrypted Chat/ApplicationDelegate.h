/*-----------------------------------------------------------------------------
 * SOURCE FILE:	ApplicationDelegate.h
 * 
 * PROGRAM:     Encrypted Chat
 * 
 * DATE:        October 4, 2009
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
#import "Encryption.h"

// Interface for the main application window
@interface ApplicationDelegate : NSObject <NSApplicationDelegate>
{
    NSWindow *window;
	
	// Client & Server Classes
	Server *server;
	Client *client;
	
	// Encryption Class
	Encryption *crypt;

	BOOL isRunning;
	
	// Main Window
    IBOutlet id logView;
	IBOutlet id encryptCheck;
	IBOutlet id decryptCheck;
    IBOutlet id connectListenButton;
	IBOutlet id inputView;
	
	// Preferences Window: Connection
	IBOutlet id remoteIP;
	IBOutlet id displayName;
	IBOutlet id modeSetting;

	// Preferences Window: Encryption
	IBOutlet id cipher;
	IBOutlet id affineMult;
	IBOutlet id affineAdd;
	IBOutlet id vigenereKey;
	
	// Testing
	IBOutlet id encryptButton;
}

@property (assign) IBOutlet NSWindow *window;

// Program Initialization & Deinitialization
- (id)init;
- (void)awakeFromNib;
- (void)initWindow;
- (void)initPreferences;
- (void)applicationDidFinishLaunching:(NSNotification *)aNotification;
- (void)dealloc;

// Main Window Events
- (IBAction)send:(id)sender;
- (IBAction)connectListen:(id)sender;

// Preferences Events
- (IBAction)modeChanged:(id)sender;

// View Formatting
- (void)scrollToBottom;
- (void)logMessage:(NSString *)msg logType:(NSString *)type;

// Connections
- (void)processMessage:(NSString *)message orData:(NSData *)data fromConnection:(ClientServerConnection *)con;
- (void)processNewConnection:(ClientServerConnection *)con;
- (void)processClosingConnection:(ClientServerConnection *)con;
- (void)connectionDidClose:(ClientServerConnection *)con;

// Testing
- (IBAction)encryptInput:(id)sender;

@end
