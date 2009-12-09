/*-----------------------------------------------------------------------------
 * SOURCE FILE:	ApplicationDelegate.h
 * 
 * PROGRAM:     Encrypted Chat
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   November 24, 2009 - Steffen L. Norgren <ironix@trollop.org>
 *                                  Added the ability to display the key being
 *                                  used to encrypt data as well as DES & AES
 *                                  encryption.
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
#import "SSCrypto.h"


// Interface for the main application window
@interface ApplicationDelegate : NSObject <NSApplicationDelegate>
{
    NSWindow *window;
	
	// Client & Server Classes
	Server *server;
	Client *client;
	
	// Encryption Classes
	Encryption *crypt;
	SSCrypto *crypto;
	NSData *cryptData;
	
	BOOL isRunning;
	
	// Main Window
    IBOutlet id logView;
	IBOutlet id encryptCheck;
	IBOutlet id decryptCheck;
    IBOutlet id connectListenButton;
	IBOutlet id inputView;
	IBOutlet id displayKeyButton;
	
	// Preferences Window: Connection
	IBOutlet id remoteIP;
	IBOutlet id displayName;
	IBOutlet id modeSetting;

	// Preferences Window: Encryption
	IBOutlet id cipher;
	IBOutlet id affineMult;
	IBOutlet id affineAdd;
	IBOutlet id vigenereKey;
	IBOutlet id cryptoKey;
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
- (IBAction)displayKey:(id)sender;

// Preferences Events
- (IBAction)modeChanged:(id)sender;
- (IBAction)cipherChanged:(id)sender;

// View Formatting
- (void)scrollToBottom;
- (void)logMessage:(NSString *)msg logType:(NSString *)type;

// Connections
- (void)processMessage:(NSString *)message orData:(NSData *)data fromConnection:(ClientServerConnection *)con;
- (void)processNewConnection:(ClientServerConnection *)con;
- (void)processClosingConnection:(ClientServerConnection *)con;
- (void)connectionDidClose:(ClientServerConnection *)con;

@end
