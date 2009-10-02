//
//  Encrypted_ChatAppDelegate.m
//  Encrypted Chat
//
//  Created by Steffen L. Norgren on 09-09-29.
//  Copyright 2009 Esurient Systems Inc.. All rights reserved.
//

#import "Encrypted_ChatAppDelegate.h"
#import "AsyncSocket.h"

#define TEXT_MSG	0
#define PORT		3141

#define READ_TIMEOUT -1 // No timeout
#define READ_TIMEOUT_EXTENSION 10.0

#define FORMAT(format, ...) [NSString stringWithFormat:(format), ##__VA_ARGS__]

@implementation Encrypted_ChatAppDelegate

@synthesize window;

#pragma mark GUI Initialization

- (id)init
{
	if(self = [super init])
	{
		inSocket = [[AsyncSocket alloc] initWithDelegate:self];
		outSocket = [[AsyncSocket alloc] initWithDelegate:self];
		connectedSockets = [[NSMutableArray alloc] initWithCapacity:1];
				
		isRunning = NO;
	}

	return self;
}

- (void)awakeFromNib
{
	[self initWindow];
	[self initPreferences];
}

- (void)initWindow
{
	[logView setString:@""];
	[inputView setString:@""];
	[encryptCheck setState:true];
}

- (void)initPreferences
{
	// Connection Preferences
	[[[modeSetting cells] objectAtIndex:0] setState:true];
	[[[modeSetting cells] objectAtIndex:1] setState:false];
	[remoteIP setStringValue:@"127.0.0.1"];
	[displayName setStringValue:@"Client"];
	
	// Encryption Preferences
	[cipherVigenere setState:true];
	[cipherAffine setState:false];
	
	[vigenereMult addItemsWithObjectValues:(NSArray *)[NSArray arrayWithObjects:
													   @"1",@"3",@"5",@"7",@"9",@"11",@"15",
													   @"17",@"19",@"21",@"23",@"25",nil]];
	
	for (int i = 0; i < 26; i++)
	{
		[vigenereAdd addItemWithObjectValue:(NSString *)[NSString stringWithFormat:@"%d", i]];
	}
	
	// Set the Vigenère cipher key
	[vigenereMult selectItemAtIndex:1];
	[vigenereAdd selectItemAtIndex:7];
	
	// Set the Affine cipher key
	[affineKey setStringValue:@"computer"];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
	NSLog(@"Ready");
	
	// Advanced options - enable the socket to contine operations even during modal dialogs, and menu browsing
	[inSocket setRunLoopModes:[NSArray arrayWithObject:NSRunLoopCommonModes]];
}

- (void)dealloc
{
	[super dealloc];
}

#pragma mark Events

- (IBAction)send:(id)sender
{
	NSData *data;

	if ([[inputView textStorage] length] > 0 && isRunning)
	{
		// Locally display chat output
		[self logMessage:[displayName stringValue] logType:@"info" newLine:false];
		[self logMessage:@" > " logType:@"info"  newLine:false];
		[self logMessage:[[inputView textStorage] string] logType:@"" newLine:true];
				
		if ([modeSetting selectedColumn] == 0)
		{
			data = [[[inputView textStorage] string] dataUsingEncoding:NSUTF8StringEncoding];
			
			[outSocket writeData:data withTimeout:-1 tag:TEXT_MSG];
		}
		else if ([modeSetting selectedColumn] == 1)
		{
			// Send to all connected clients
			for (int i = 0; i < [connectedSockets count]; i++)
			{
				data = [[[inputView textStorage] string] dataUsingEncoding:NSUTF8StringEncoding];
				
				[[connectedSockets objectAtIndex:i] writeData:data withTimeout:-1 tag:TEXT_MSG];
			}			
		}
	}
	
	// Clear the input window
	[inputView setString:@""];
}

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

- (IBAction)connectListen:(id)sender
{
	switch ([modeSetting selectedColumn])
	{
		case 0:
			if (!isRunning)
			{
				NSError *err;
				
				if(![outSocket connectToHost:[remoteIP stringValue] onPort:3141 error:&err])
				{
					NSLog(@"Error: %@", err);
				}
				
				isRunning = true;
				[connectListenButton setTitle:@"Disconnect"];
			}
			else
			{
				[outSocket disconnect];
				[self logMessage:@"Disconnected" logType:@"info" newLine:true];
				isRunning = false;
				[connectListenButton setTitle:@"Connect"];
			}
			break;
		case 1:
			if(!isRunning)
			{
				int port = PORT;
				
				NSError *error = nil;
				if(![inSocket acceptOnPort:port error:&error])
				{
					[self logMessage:FORMAT(@"Error starting server: %@", error)
							 logType:@"error" newLine:true];
					return;
				}
				
				[self logMessage:FORMAT(@"Echo server started on port %hu", [inSocket localPort])
						 logType:@"info" newLine:true];
				isRunning = true;
				
				[connectListenButton setTitle:@"Disconnect"];
			}
			else
			{
				// Stop accepting connections
				[inSocket disconnect];
				
				// Stop any client connections
				int i;
				for(i = 0; i < [connectedSockets count]; i++)
				{
					// Call disconnect on the socket,
					// which will invoke the onSocketDidDisconnect: method,
					// which will remove the socket from the list.
					[[connectedSockets objectAtIndex:i] disconnect];
				}
				
				[self logMessage:@"Stopped Echo server" logType:@"info" newLine:true];
				isRunning = false;
				
				[connectListenButton setTitle:@"Listen"];
			}
			break;
		default:
			break;
	}
}

#pragma mark GUI Modifiers

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

- (void)logMessage:(NSString *)msg logType:(NSString *)type newLine:(Boolean)newLine
{
	NSString *paragraph;
	
	if (newLine)
		paragraph = [NSString stringWithFormat:@"%@\n", msg];
	else
		paragraph = [NSString stringWithFormat:@"%@", msg];
	
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

#pragma mark Sockts

- (void)onSocket:(AsyncSocket *)sock didAcceptNewSocket:(AsyncSocket *)newSocket
{
	[connectedSockets addObject:newSocket];
}

- (void)onSocket:(AsyncSocket *)sock didConnectToHost:(NSString *)host port:(UInt16)port
{
	if ([modeSetting selectedColumn] == 0)
		[self logMessage:FORMAT(@"Connected to %@:%hu", host, port)
				 logType:@"info" newLine:true];
	else
		[self logMessage:FORMAT(@"Accepted client %@:%hu", host, port)
				 logType:@"info" newLine:true];
	
	[sock readDataToData:[AsyncSocket CRLFData] withTimeout:READ_TIMEOUT tag:0];
}

- (void)onSocket:(AsyncSocket *)sock didWriteDataWithTag:(long)tag
{
	if(tag == TEXT_MSG)
	{
		[sock readDataToData:[AsyncSocket CRLFData] withTimeout:READ_TIMEOUT tag:0];
	}
}

- (void)onSocket:(AsyncSocket *)sock didReadData:(NSData *)data withTag:(long)tag
{
	NSData *strData = [data subdataWithRange:NSMakeRange(0, [data length] - 2)];
	NSString *msg = [[[NSString alloc] initWithData:strData encoding:NSUTF8StringEncoding] autorelease];
	
	if(msg)
	{
		[self logMessage:msg logType:@"" newLine:true];
	}
	else
	{
		[self logMessage:@"Error converting received data into UTF-8 String"
			   logType:@"error" newLine:true];
	}
	
	// Even if we were unable to write the incoming data to the log,
	// we're still going to echo it back to the client.
	[sock writeData:data withTimeout:-1 tag:TEXT_MSG];
}

/**
 * This method is called if a read has timed out.
 * It allows us to optionally extend the timeout.
 * We use this method to issue a warning to the user prior to disconnecting them.
 **/
- (NSTimeInterval)onSocket:(AsyncSocket *)sock
  shouldTimeoutReadWithTag:(long)tag
				   elapsed:(NSTimeInterval)elapsed
				 bytesDone:(CFIndex)length
{
	if(elapsed <= READ_TIMEOUT)
	{
		return READ_TIMEOUT_EXTENSION;
	}
	
	return 0.0;
}

- (void)onSocket:(AsyncSocket *)sock willDisconnectWithError:(NSError *)err
{
	[self logMessage:FORMAT(@"Client Disconnected: %@:%hu", [sock connectedHost], [sock connectedPort])
			 logType:@"info" newLine:true];
}

- (void)onSocketDidDisconnect:(AsyncSocket *)sock
{
	[connectedSockets removeObject:sock];
}

@end
