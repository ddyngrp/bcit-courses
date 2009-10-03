//
//  Encrypted_ChatAppDelegate.m
//  Encrypted Chat
//
//  Created by Steffen L. Norgren on 09-09-29.
//  Copyright 2009 Esurient Systems Inc.. All rights reserved.
//

#import "Encrypted_ChatAppDelegate.h"

#define FORMAT(format, ...) [NSString stringWithFormat:(format), ##__VA_ARGS__]

@implementation Encrypted_ChatAppDelegate

@synthesize window;

#pragma mark GUI Initialization

- (id)init
{
	if(self = [super init])
		isRunning = NO;

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
	[encryptCheck setState:YES];
}

- (void)initPreferences
{
	// Connection Preferences
	[[[modeSetting cells] objectAtIndex:0] setState:YES];
	[[[modeSetting cells] objectAtIndex:1] setState:NO];
	[remoteIP setStringValue:@"127.0.0.1"];
	[displayName setStringValue:@"Client"];
	
	// Encryption Preferences
	[cipherVigenere setState:YES];
	[cipherAffine setState:NO];
	
	[vigenereMult addItemsWithObjectValues:(NSArray *)[NSArray arrayWithObjects:
													   @"1",@"3",@"5",@"7",@"9",@"11",@"15",
													   @"17",@"19",@"21",@"23",@"25",nil]];
	
	for (int i = 0; i < 26; i++)
		[vigenereAdd addItemWithObjectValue:(NSString *)[NSString stringWithFormat:@"%d", i]];
	
	// Set the Vigenère cipher key
	[vigenereMult selectItemAtIndex:1];
	[vigenereAdd selectItemAtIndex:7];
	
	// Set the Affine cipher key
	[affineKey setStringValue:@"computer"];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
	NSLog(@"Ready");
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
		[self logMessage:FORMAT(@"%@ > ", [displayName stringValue]) logType:@"info"];
		[self logMessage:FORMAT(@"%@\n", [[inputView textStorage] string]) logType:@""];
				
		if ([modeSetting selectedColumn] == 0)
		{
			data = [FORMAT(@"%@ > %@\n", [displayName stringValue], [[inputView textStorage] string])
					dataUsingEncoding:NSUTF8StringEncoding];
		}
		else if ([modeSetting selectedColumn] == 1)
		{
			data = [FORMAT(@"%@ > %@\n", [displayName stringValue], [[inputView textStorage] string])
					dataUsingEncoding:NSUTF8StringEncoding];
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
			isRunning = YES;
			break;
		case 1:
			isRunning = YES;
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

@end
