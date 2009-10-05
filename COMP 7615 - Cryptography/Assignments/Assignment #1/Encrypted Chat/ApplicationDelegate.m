/*-----------------------------------------------------------------------------
 * SOURCE FILE:	ApplicationDelegate.m - Main application's delegate
 * 
 * PROGRAM:     Encrypted Chat
 * 
 * FUNCTIONS:   - (id)init
 *              - (void)awakeFromNib
 *              - (void)initWindow
 *              - (void)initPreferences
 *              - (void)applicationDidFinishLaunching:
 *                                 (NSNotification *)aNotification
 *              - (void)dealloc
 *              - (IBAction)send:(id)sender
 *              - (IBAction)modeChanged:(id)sender
 *              - (IBAction)connectListen:(id)sender
 *              - (void)scrollToBottom
 *              - (void)logMessage:(NSString *)msg logType:(NSString *)type
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * NOTES: This is the main delegate for the application. It handles all GUI
 *        and client/server functions.
 *
 *---------------------------------------------------------------------------*/

#import "ApplicationDelegate.h"

#define PORT 3141
#define FORMAT(format, ...) [NSString stringWithFormat:(format), ##__VA_ARGS__]

@implementation Encrypted_ChatAppDelegate

@synthesize window; // Generates accessor methods and garbage collection

#pragma mark GUI Initialization

/*-----------------------------------------------------------------------------
 * FUNCTION:    init
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (id)init
 * 
 * RETURNS: The delegate id for this class.
 * 
 * NOTES: Aside from initializing the delegate, this also sets the current
 *        running state to NO.
 *
 *----------------------------------------------------------------------------*/
- (id)init
{
	if(self = [super init]) {
		crypt = [[Encryption alloc] init];
		isRunning = NO;
	}

	return self;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    awakeFromNib
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (void)awakeFromNib
 * 
 * RETURNS: void
 * 
 * NOTES: Called once the application Nib files have been loaded. This simply
 *        calls other initialization functions.
 *
 *----------------------------------------------------------------------------*/
- (void)awakeFromNib
{
	[self initWindow];
	[self initPreferences];
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    initWindow
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (void)initWindow
 * 
 * RETURNS: void
 * 
 * NOTES: Initializes the default settings in the main appliation window.
 *
 *----------------------------------------------------------------------------*/
- (void)initWindow
{
	[logView setString:@""];
	[inputView setString:@""];
	[encryptCheck setState:YES];
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    initPreferences
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (void)initPreferences
 * 
 * RETURNS: void
 * 
 * NOTES: Initializes the default preferences values in the preferences window.
 *
 *----------------------------------------------------------------------------*/
- (void)initPreferences
{
	// Connection Preferences
	[[[modeSetting cells] objectAtIndex:0] setState:YES];
	[[[modeSetting cells] objectAtIndex:1] setState:NO];
	[remoteIP setStringValue:@"127.0.0.1"];
	[displayName setStringValue:@"Client"];
	
	// Encryption Preferences
	[[[cipher cells] objectAtIndex:0] setState:YES]; // Vigenère cipher
	[[[cipher cells] objectAtIndex:1] setState:NO]; // Affine cipher
	
	[affineMult addItemsWithObjectValues:(NSArray *)[NSArray arrayWithObjects:
													   @"1",@"3",@"5",@"7",@"9",@"11",@"15",
													   @"17",@"19",@"21",@"23",@"25",nil]];
	
	for (int i = 0; i < 26; i++)
		[affineAdd addItemWithObjectValue:(NSString *)[NSString stringWithFormat:@"%d", i]];
	
	// Set the Vigenère cipher key
	[affineMult selectItemAtIndex:1];
	[affineAdd selectItemAtIndex:7];
	
	// Set the Affine cipher key
	[vigenereKey setStringValue:@"computer"];
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    applicationDidFinishLaunching
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (void)applicationDidFinishLaunching:
 *                               (NSNotification *)aNotification
 * 
 * RETURNS: void
 * 
 * NOTES: Called once the application finished launching successfully.
 *
 *----------------------------------------------------------------------------*/
- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
	NSLog(@"Ready");
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    dealloc
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (void)dealloc
 * 
 * RETURNS: void
 * 
 * NOTES: Called upon application termination. Handles garbage collection.
 *
 *----------------------------------------------------------------------------*/
- (void)dealloc
{
	[client release];
	[server release];
	[crypt release];
	[super dealloc];
}

#pragma mark Events

/*-----------------------------------------------------------------------------
 * FUNCTION:    send
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (IBAction)send:(id)sender
 *                        sender: the delegate ID of the sender
 * 
 * RETURNS: void
 * 
 * NOTES: Event handler for the send button. Manages posting and sending text.
 *        Additionally encrypts outbound text.
 *
 *----------------------------------------------------------------------------*/
- (IBAction)send:(id)sender
{
	if ([[inputView textStorage] length] > 0 && isRunning)
	{
		NSString *encrypt = [[NSString alloc] autorelease];
		NSString *message = [[NSString alloc] autorelease];

		// Encrypt & decrypt the string using selected method
		if ([cipher selectedRow] == 0)
			encrypt = [crypt encryptVigenere:[[inputView textStorage] string]
								   cipherKey:[vigenereKey stringValue]];
		else if ([cipher selectedRow] == 1)
			encrypt = [crypt encryptAffine:[[inputView textStorage] string]
								   multNum:[[affineMult objectValueOfSelectedItem] intValue]
									addNum:[[affineAdd objectValueOfSelectedItem] intValue]];
		
		// Set whether the outbound message is encrypted or not.
		if ([encryptCheck state] == NO)
			message = [[inputView textStorage] string];
		else if ([encryptCheck state] == YES)
			message = encrypt;
		
		// Locally display chat output
		[self logMessage:FORMAT(@"%@ > ", [displayName stringValue]) logType:@"info"];
		[self logMessage:FORMAT(@"%@\n", [[inputView textStorage] string]) logType:@""];			
		
		// Send the string
		if ([modeSetting selectedColumn] == 0)
			[client sendString:FORMAT(@"%@", message)];
		else if ([modeSetting selectedColumn] == 1)
			[server sendStringToAll:FORMAT(@"%@", message)];
	}
	
	// Clear the input window
	[inputView setString:@""];
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    modeChanged
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (IBAction)modeChanged:(id)sender
 *                        sender: the delegate ID of the sender
 * 
 * RETURNS: void
 * 
 * NOTES: Event handler when the mode is changed. Also updates the text for
 *        the Connect/Listen button to be appropriate for the selected mode.
 *
 *----------------------------------------------------------------------------*/
- (IBAction)modeChanged:(id)sender
{
	if ([modeSetting selectedColumn] == 0)
	{
		if ([[displayName stringValue] compare:@"Server"] == NSOrderedSame)
			[displayName setStringValue:@"Client"];

		[connectListenButton setTitle:@"Connect"];
	}
	else if ([modeSetting selectedColumn] == 1)
	{
		if ([[displayName stringValue] compare:@"Client"] == NSOrderedSame)
			[displayName setStringValue:@"Server"];

		[connectListenButton setTitle:@"Listen"];
	}
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    connectListen
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (IBAction)connectListen:(id)sender
 *                        sender: the delegate ID of the sender
 * 
 * RETURNS: void
 * 
 * NOTES: Event handler for the Connect/Listen button. Initiates a connection
 *        to a server or initiates listening for incomming connections.
 *
 *----------------------------------------------------------------------------*/
- (IBAction)connectListen:(id)sender
{	
	switch ([modeSetting selectedColumn])
	{
		case 0:
			if (!isRunning) {
				client = [[Client alloc] initWithHost:[remoteIP stringValue]
												 port:PORT
											 delegate:self];
				
				unsigned int error = [client connect];
				
				if (error == InitOK) {
					[self logMessage:FORMAT(@"Connected to %@:%d\n", [client remoteHost], PORT)
							 logType:@"info"];
					
					[connectListenButton setTitle:@"Disconnect"];
					[modeSetting setEnabled:NO];
					[remoteIP setEnabled:NO];
					[displayName setEnabled:NO];
					isRunning = YES;					
				}
				else {
					[self logMessage:FORMAT(@"Error (%hu): Unable to connect to %@:%d\n",
											error, [client remoteHost], [client remotePort])
											logType:@"error"];
					[client release];
				}
			}
			else {
				[self logMessage:FORMAT(@"Disconnected from %@:%d\n", [client remoteHost], PORT)
						 logType:@"info"];
				
				[client disconnect];
				[client release];
				
				[connectListenButton setTitle:@"Connect"];
				[modeSetting setEnabled:YES];
				[remoteIP setEnabled:YES];
				[displayName setEnabled:YES];
				isRunning = NO;
			}

			break;
		case 1:
			if (!isRunning) {
				server = [[Server alloc] initWithPort:3141 delegate:self];
				[server setListenAddress:ListenAll];
				
				unsigned int error = [server startListening];
				
				if (error == InitOK) {				
					[connectListenButton setTitle:@"Disconnect"];
					[modeSetting setEnabled:NO];
					[remoteIP setEnabled:NO];
					[displayName setEnabled:NO];
					isRunning = YES;
					
					[self logMessage:@"Listening for connections.\n" logType:@"info"];
				}
				else {
					[self logMessage:FORMAT(@"Error (%hu): unable to start listening.\n", error) logType:@"error"];
					[server release];
				}
			}
			else {
				[server	stopListening];
				[server release];
				
				[connectListenButton setTitle:@"Listen"];
				[modeSetting setEnabled:YES];
				[remoteIP setEnabled:YES];
				[displayName setEnabled:YES];
				isRunning = NO;

				[self logMessage:@"Stopped listening for connections.\n" logType:@"info"];
			}
			break;
		default:
			break;
	}
}

#pragma mark GUI Modifiers

/*-----------------------------------------------------------------------------
 * FUNCTION:    scrollToBottom
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (void)scrollToBottom
 * 
 * RETURNS: void
 * 
 * NOTES: Scrolls the chat window to the bottom.
 *
 *----------------------------------------------------------------------------*/
- (void)scrollToBottom
{
	NSScrollView *scrollView = [logView enclosingScrollView];
	NSPoint newScrollOrigin;
	
	if ([[scrollView documentView] isFlipped])
		newScrollOrigin = NSMakePoint(0.0, NSMaxY([[scrollView documentView] frame]));
	else
		newScrollOrigin = NSMakePoint(0.0, 0.0);
	
	[[scrollView documentView] scrollPoint:newScrollOrigin];
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    logMessage
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (void)logMessage:(NSString *)msg logType:(NSString *)type
 *                    msg: The message to be posted to the chat window
 *                    logType: The type of message {error, info}
 * 
 * RETURNS: void
 * 
 * NOTES: Posts a message to the main chat window.
 *
 *----------------------------------------------------------------------------*/
- (void)logMessage:(NSString *)msg logType:(NSString *)type
{
	NSString *paragraph = [NSString stringWithFormat:@"%@", msg];
	
	NSMutableDictionary *attributes = [NSMutableDictionary dictionaryWithCapacity:1];
	
	if ([type compare:@"error"] == NSOrderedSame)
		[attributes setObject:[NSColor redColor] forKey:NSForegroundColorAttributeName];
	else if ([type compare:@"info"] == NSOrderedSame)
		[attributes setObject:[NSColor purpleColor] forKey:NSForegroundColorAttributeName];
	else
		[attributes setObject:[NSColor blackColor] forKey:NSForegroundColorAttributeName];
	
	NSAttributedString *as = [[NSAttributedString alloc] initWithString:paragraph attributes:attributes];
	[as autorelease];
	
	[[logView textStorage] appendAttributedString:as];
	[self scrollToBottom];
}

#pragma mark Client & Server Common Methods

/*-----------------------------------------------------------------------------
 * FUNCTION:    processMessage
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (void)processMessage:(NSString *)message orData:(NSData *)data
 *                                   fromConnection:(ClientServerConnection *)con
 *                    message: string that has been received
 *                    data: raw data as an NSData object
 *                    con: connection the message was received from
 * 
 * RETURNS: void
 * 
 * NOTES: Sent to the delegate after data has been received by one of the
 *        connections.
 *
 *----------------------------------------------------------------------------*/
- (void)processMessage:(NSString *)message orData:(NSData *)data fromConnection:(ClientServerConnection *)con
{
	NSString *decrypt = [[NSString alloc] autorelease];
	
	// Decrypt the string using selected method
	if ([cipher selectedRow] == 0)
		decrypt = [crypt decryptVigenere:message
							   cipherKey:[vigenereKey stringValue]];
	else if ([cipher selectedRow] == 1)
		decrypt = [crypt decryptAffine:message
							   multNum:[[affineMult objectValueOfSelectedItem] intValue]
								addNum:[[affineAdd objectValueOfSelectedItem] intValue]];

	// Output the string
	if ([decryptCheck state] == YES)
		[self logMessage:FORMAT(@"%@\n", decrypt) logType:@""];
	else if ([decryptCheck state] == NO)
		[self logMessage:FORMAT(@"%@\n", message) logType:@""];
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    processNewConnection
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (void)processNewConnection:(ClientServerConnection *)con
 *                    con: connection the message was received from
 * 
 * RETURNS: void
 * 
 * NOTES: Will be sent the delegate after a new connection has been
 *        successfully established.
 *
 *----------------------------------------------------------------------------*/
- (void)processNewConnection:(ClientServerConnection *)con
{
	[self logMessage:FORMAT(@"Client %@ connected.\n", con) logType:@"info"];
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    processClosingConnection
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (void)processClosingConnection:(ClientServerConnection *)con
 *                    con: connection the message was received from
 * 
 * RETURNS: void
 * 
 * NOTES: Will be sent the delegate just before the connection will be closed.
 *
 *----------------------------------------------------------------------------*/
- (void)processClosingConnection:(ClientServerConnection *)con
{
	[self logMessage:FORMAT(@"Client %@ disconnected.\n", con) logType:@"info"];
}

#pragma mark Client Methods

/*-----------------------------------------------------------------------------
 * FUNCTION:    connectionDidClose
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (void)connectionDidClose:(ClientServerConnection *)con
 *                    con: connection the message was received from
 * 
 * RETURNS: void
 * 
 * NOTES: Will be sent the delegate after the connection closed.
 *
 *----------------------------------------------------------------------------*/
- (void)connectionDidClose:(ClientServerConnection *)con
{
	[self logMessage:FORMAT(@"%@:%d closed connection.\n", [client remoteHost], PORT)
			 logType:@"error"];
	
	[connectListenButton setTitle:@"Connect"];
	[modeSetting setEnabled:YES];
	[remoteIP setEnabled:YES];
	[displayName setEnabled:YES];
	isRunning = NO;
}

@end
