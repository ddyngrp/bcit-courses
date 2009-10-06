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
 *              - (IBAction)connect:(id)sender
 *              - (IBAction)sendCommand:(id)sender
 *              - (void)scrollToBottom
 *              - (void)logMessage:(NSString *)msg logType:(NSString *)type
 *              - (void)processNewConnection:(ClientServerConnection *)con
 *              - (void)processClosingConnection:(ClientServerConnection *)con
 *              - (void)processMessage:(NSString *)message orData:(NSData *)data
 *                      fromConnection:(ClientServerConnection *)con
 *              - (void)connectionDidClose:(ClientServerConnection *)con
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
 *        and client functions.
 *
 *---------------------------------------------------------------------------*/

#import "FileClientAppDelegate.h"

#define PORT_CONTROL 7001
#define PORT_DATA 7000
#define FORMAT(format, ...) [NSString stringWithFormat:(format), ##__VA_ARGS__]

@implementation FileClientAppDelegate

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
	if(self = [super init]) {
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
	[commandText setEnabled:NO];
	[sendButton setEnabled:NO];
	[serverIP setEnabled:YES];

	[commandText setStringValue:@""];
	[serverIP setStringValue:@"127.0.0.1"];
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
	[saveFile release];
	[client release];
	[server release];
	[super dealloc];
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    connect
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (IBAction)connect:(id)sender
 *                        sender: the delegate ID of the sender
 * 
 * RETURNS: void
 * 
 * NOTES: Event handler for the Listen button. Initiates connection to
 *        the server and listens incomming data connections.
 *
 *----------------------------------------------------------------------------*/
- (IBAction)connect:(id)sender
{
	if (!isRunning) {
		client = [[Client alloc] initWithHost:[serverIP stringValue]
										 port:PORT_CONTROL delegate:self];
		
		unsigned int error = [client connect];
		
		if (error == InitOK) {
			[self logMessage:FORMAT(@"Connected to %@:%d\n", [client remoteHost], PORT_CONTROL)
					 logType:@"info"];
			
			// Start listening on the data channel
			server = [[Server alloc] initWithPort:PORT_DATA delegate:self];
			[server setListenAddress:ListenAll];
			
			error = [server startListening];
			
			// If listening on the data port succeeds, proceed
			if (error == InitOK) {
				[connectButton setTitle:@"Disconnect"];
				[commandText setEnabled:YES];
				[sendButton setEnabled:YES];
				[serverIP setEnabled:NO];
				isRunning = YES;
				
				[self logMessage:FORMAT(@"Listening for data connections on port %d.\n", [server serverPort])
						 logType:@"info"];
			}
			else {
				[self logMessage:FORMAT(@"Error (%hu): unable to start listening.\n", error)
						 logType:@"error"];
				[server release];
			}			
		}
		else {
			[self logMessage:FORMAT(@"Error (%hu): Unable to connect to %@:%d\n",
									error, [client remoteHost], [client remotePort])
					 logType:@"error"];
			[client release];
		}
	}
	else {
		[self logMessage:FORMAT(@"Disconnected from %@:%d\n", [client remoteHost], PORT_CONTROL)
				 logType:@"info"];
		
		isRunning = NO;

		[server stopListening];
		[client disconnect];
		[server release];
		[client release];
		
		[connectButton setTitle:@"Connect"];
		[commandText setEnabled:NO];
		[sendButton setEnabled:NO];
		[serverIP setEnabled:YES];
	}
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    sendCommand
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (IBAction)sendCommand:(id)sender
 *                        sender: the delegate ID of the sender
 * 
 * RETURNS: void
 * 
 * NOTES: Send a command to the server.
 *
 *----------------------------------------------------------------------------*/
- (IBAction)sendCommand:(id)sender
{
	if ([[[commandText stringValue] uppercaseString] rangeOfString:@"GET "].location != NSNotFound) {
		saveFile = [[NSString alloc] initWithString:FORMAT(@"/Users/ironix/Desktop%@",
														   [[commandText stringValue] substringFromIndex:4])];
		[client sendString:[commandText stringValue]];
	}
	else if ([[[commandText stringValue] uppercaseString] rangeOfString:@"SEND "].location != NSNotFound) {
		[client sendString:[commandText stringValue]];
		// Grab the data send send to the server
		NSData *sendData = [NSData dataWithContentsOfFile:[[commandText stringValue] substringFromIndex:5]];
		[client sendData:sendData];
	}
	else {
		[client sendString:[commandText stringValue]];
	}

	
	[commandText setStringValue:@""];
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
	[self logMessage:FORMAT(@"Server %@ connected to data channel.\n", con) logType:@"info"];
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
	[self logMessage:FORMAT(@"Server %@ disconnected from data channel.\n", con) logType:@"info"];
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
	if (message)
		[self logMessage:message logType:@""];
	
	if (data) {
		// Create the file if necessary
		if ([NSFileHandle fileHandleForReadingAtPath:saveFile] == nil) {
			[[NSFileManager defaultManager] createFileAtPath:saveFile contents:nil attributes:nil];
		}
		
		NSFileHandle *writeFile = [NSFileHandle fileHandleForWritingAtPath:saveFile];
		
		[writeFile seekToEndOfFile];
		[writeFile writeData:data];
		[writeFile closeFile];
	}
}

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
	if (isRunning) {
		[self logMessage:FORMAT(@"%@:%d closed connection.\n", [client remoteHost], [client remotePort])
				 logType:@"error"];
	
		[server stopListening];
		[server release];
		[client release];
		
		[connectButton setTitle:@"Connect"];
		[commandText setEnabled:NO];
		[sendButton setEnabled:NO];
		[serverIP setEnabled:YES];
		isRunning = NO;
	}
}

@end
