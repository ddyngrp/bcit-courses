/*-----------------------------------------------------------------------------
 * SOURCE FILE:	FileServerAppDelegate.m
 * 
 * PROGRAM:     Encrypted Chat
 * 
 * FUNCTIONS:   - (id)init
 *              - (void)awakeFromNib
 *              - (void)initWindow
 *              - (void)applicationDidFinishLaunching:
 *                      (NSNotification *)aNotification
 *              - (void)dealloc
 *              - (IBAction)listenForConnect:(id)sender
 *              - (void)scrollToBottom
 *              - (void)logMessage:(NSString *)msg logType:(NSString *)type
 *              - (void)processNewConnection:(ClientServerConnection *)con
 *              - (void)processClosingConnection:(ClientServerConnection *)con
 *              - (void)processMessage:(NSString *)message orData:(NSData *)data
 *                      fromConnection:(ClientServerConnection *)con
 *              - (void)sendFile:(NSString *)fileName
 *                      toConnection:(Client *)con
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
	if(self = [super init]) {
		// Client data connection pool
		dataConn = [[NSMutableArray alloc] init];
		basePath = [[NSString alloc] initWithString:[[@"~/Desktop/ServerFiles"
													  stringByStandardizingPath]
													 stringByAppendingString:@"/"]];
		
		// Create server file directory if needed
		NSFileManager *manager = [NSFileManager alloc];
		[manager createDirectoryAtPath:basePath withIntermediateDirectories:YES attributes:nil error:nil];
		
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
	[dataConn release];
	[saveFile release];
	[server release];
	[super dealloc];
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    listenForConnect
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (IBAction)listenForConnect:(id)sender
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
	// Only process messages on the control channel
	if (message) {
		NSString *fileName;
		BOOL sendFileToClient = NO;
		BOOL newConnection = YES;
		
		if ([[message uppercaseString] rangeOfString:@"GET "].location != NSNotFound && [message length] < 30) {
			[self logMessage:FORMAT(@"Client %@ command: %@\n", con, message) logType:@""];
			fileName = [message substringFromIndex:4];
			
			sendFileToClient = YES;
		}
		else if ([[message uppercaseString] rangeOfString:@"SEND "].location != NSNotFound && [message length] < 30) {
			[self logMessage:FORMAT(@"Client %@ command: %@\n", con, message) logType:@""];
			saveFile = [[NSString alloc] initWithString:[message substringFromIndex:5]];
		}
		else if ([[message uppercaseString] rangeOfString:@"HELP"].location != NSNotFound && [message length] < 30) {
			[self logMessage:FORMAT(@"Client %@ command: %@\n", con, message) logType:@""];
			[server sendString:@"Server: Available commands: GET [file], SEND [file], HELP.\n" toConnection:con];
			newConnection = NO;
		}
		else {
			if ([message length] > 30) {
				[message writeToFile:[basePath stringByAppendingString:saveFile] atomically:NO
							encoding:NSStringEncodingConversionAllowLossy error:nil];
				[saveFile release];
			}
			else {
				[server sendString:@"Server: Invalid Command. For a lost of available commands, enter HELP.\n"
					  toConnection:con];
				newConnection = NO;
			}
		}
		
		// Search for existing data connection
		for (int i = 0; i < [dataConn count]; i++) {
			if ([[(Client*)[dataConn objectAtIndex:i] remoteHost] compare:[con remoteAddress]] == NSOrderedSame) {
				// Remove the connection if it exists and is inactive
				if (![(Client*)[dataConn objectAtIndex:i] isConnected])
					[dataConn removeObjectAtIndex:i];
				else
					newConnection = NO;
			}
		}
		
		// Connect and add to the connection pool
		if (newConnection) {
			[self newDataConnection:con];
			newConnection = NO;
		}

		if (sendFileToClient) {
			// Search for existing data connection
			for (int i = 0; i < [dataConn count]; i++) {
				if ([[(Client*)[dataConn objectAtIndex:i] remoteHost] compare:[con remoteAddress]] == NSOrderedSame) {
					// Connection found send file
					[self sendFile:[basePath stringByAppendingString:fileName]
					  toConnection:(Client*)[dataConn objectAtIndex:i]];
					sendFileToClient = NO;
				}
			}
		}
	}
	else if (data) {
		// Create the file if necessary
		if ([NSFileHandle fileHandleForReadingAtPath:[basePath stringByAppendingString:saveFile]] == nil)
			[[NSFileManager defaultManager] createFileAtPath:[basePath stringByAppendingString:saveFile]
													contents:nil attributes:nil];
		
		NSFileHandle *writeFile = [NSFileHandle fileHandleForWritingAtPath:[basePath stringByAppendingString:saveFile]];
		
		[writeFile seekToEndOfFile];
		[writeFile writeData:data];
		[writeFile closeFile];
	}
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    newDataConnection
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (void)newDataConnection:(ClientServerConnection *)con
 *                    con: connection to send the file to
 * 
 * RETURNS: void
 * 
 * NOTES: Connects to the client and adds the connection to the connection pool.
 *
 *----------------------------------------------------------------------------*/
- (void)newDataConnection:(ClientServerConnection *)con
{
	Client *client = [[Client alloc] initWithHost:[con remoteAddress] port:PORT_DATA delegate:self];
	
	unsigned int error = [client connect];
	
	if (error == InitOK) {
		[self logMessage:FORMAT(@"Connected to data channel on %@:%d\n", [client remoteHost], PORT_DATA)
				 logType:@"info"];
		
		// Add connection to the pool
		[dataConn addObject:client];
	}
	else {
		[self logMessage:FORMAT(@"Error (%hu): Unable to connect to %@:%d\n",
								error, [client remoteHost], [client remotePort])
				 logType:@"error"];
		[client release];
	}	
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    sendFile
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (void)sendFile:(NSString *)fileName toConnection:(Client *)con
 *                    fileName: file to send
 *                    con: connection to send the file to
 * 
 * RETURNS: void
 * 
 * NOTES: Sends a file to a connected client.
 *
 *----------------------------------------------------------------------------*/

- (void)sendFile:(NSString *)fileName toConnection:(Client *)con
{
	NSData *sendData = [NSData dataWithContentsOfFile:fileName];
	
	if ([sendData bytes] == 0)
		[con sendString:@"Server: Error, file does not exist.\n"];
	else
		[con sendData:sendData];
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
	[self logMessage:FORMAT(@"%@:%d closed connection.\n", [con remoteAddress], [con remotePort])
			 logType:@"error"];
}

@end