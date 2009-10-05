/*-----------------------------------------------------------------------------
 * SOURCE FILE:	FileServerAppDelegate.m
 * 
 * PROGRAM:     Encrypted Chat
 * 
 * FUNCTIONS:   - (id)init
 *              - (void)awakeFromNib
 *              - (void)initWindow
 *              - (void)applicationDidFinishLaunching:
 *                                 (NSNotification *)aNotification
 *              - (void)dealloc
 *              - (IBAction)listen:(id)sender
 *              - (void)scrollToBottom
 *              - (void)logMessage:(NSString *)msg logType:(NSString *)type
 *              - (void)processNewConnection:(ClientServerConnection *)con
 *              - (void)processClosingConnection:(ClientServerConnection *)con
 *              - (void)processMessage:(NSString *)message orData:(NSData *)data
 *                      fromConnection:(ClientServerConnection *)con
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
 *        and server functions.
 *
 *---------------------------------------------------------------------------*/

#import "FileServerAppDelegate.h"

#define PORT_CONTROL 7001
#define PORT_DATA 7000
#define FORMAT(format, ...) [NSString stringWithFormat:(format), ##__VA_ARGS__]

@implementation FileServerAppDelegate

@synthesize window;

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
	if(self = [super init])
		isRunning = NO;
	
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
	NSLog(@"Server Ready");
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
	[server release];
	[super dealloc];
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    listen
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (IBAction)listen:(id)sender
 *                        sender: the delegate ID of the sender
 * 
 * RETURNS: void
 * 
 * NOTES: Event handler for the Listen button. Initiates listening for
 *        incomming connections.
 *
 *----------------------------------------------------------------------------*/
- (IBAction)listenForConnect:(id)sender
{
	if (!isRunning) {
		server = [[Server alloc] initWithPort:PORT_CONTROL delegate:self];
		[server setListenAddress:ListenAll];
		
		unsigned int error = [server startListening];
		
		if (error == InitOK) {
			[listenButton setTitle:@"Disconnect"];
			isRunning = YES;
			
			[self logMessage:FORMAT(@"Listening for connections on port %d.\n", [server serverPort])
					 logType:@"info"];
		}
		else {
			[self logMessage:FORMAT(@"Error (%hu): unable to start listening.\n", error)
					 logType:@"error"];
			[server release];
		}
	}
	else {
		[server stopListening];
		[server release];
		
		[listenButton setTitle:@"Listen"];
		isRunning = NO;
		
		[self logMessage:@"Stopped listening for connections.\n" logType:@"info"];
	}

}

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
 * NOTES: Scrolls the log window to the bottom.
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
 *                    msg: The message to be posted
 *                    logType: The type of message {error, info}
 * 
 * RETURNS: void
 * 
 * NOTES: Posts a message to the main log window.
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
 * NOTES: Sent to the delegate when a client closes the connection.
 *
 *----------------------------------------------------------------------------*/
- (void)processClosingConnection:(ClientServerConnection *)con
{
	[self logMessage:FORMAT(@"Client %@ disconnected.\n", con) logType:@"info"];
}

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
	// Remove all non alphabetic characters from the string
	NSString *input = [[message stringByReplacingOccurrencesOfString:@"\r\n" withString:@""] autorelease];
	
	if ([input compare:@"GET"] == NSOrderedSame) {
		[self logMessage:FORMAT(@"Client %@ command: GET\n, Waiting for file name...\n", con) logType:@""];
	}
	else if ([input compare:@"SEND"] == NSOrderedSame) {
		[self logMessage:FORMAT(@"Client %@ command: SEND\n, Waiting for data...", con) logType:@""];
	}
	
	// This might have something to do with receiving, not sending.
	//		
	//		NSFileHandle *outfile = [NSFileHandle fileHandleForReadingAtPath: @"/Users/ironix/Desktop/test.txt"];
	//		
	//		if (outfile == nil)
	//			[self logMessage:@"File not found.\n" logType:@""];
	//		else
	//			[con initWithFileHandle:outfile delegate:self];
}



@end