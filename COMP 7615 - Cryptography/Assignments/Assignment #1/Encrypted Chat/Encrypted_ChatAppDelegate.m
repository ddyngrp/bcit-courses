//
//  Encrypted_ChatAppDelegate.m
//  Encrypted Chat
//
//  Created by Steffen L. Norgren on 09-09-29.
//  Copyright 2009 Esurient Systems Inc.. All rights reserved.
//

#import "Encrypted_ChatAppDelegate.h"

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
	[encryptCheck setState:true];
}

- (void)initPreferences
{
	// Connection Preferences
	[modeClient setState:true];
	[modeServer setState:false];
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

- (void)dealloc
{
	[super dealloc];
}

#pragma mark GUI Controls

- (IBAction)send:(id)sender
{
	if ([[inputView textStorage] length] > 0)
	{
		// Locally display chat output
		[self logMessage:[displayName stringValue] logType:@"info"];
		[self logMessage:@" > " logType:@"info"];
		[self logMessage:[[inputView textStorage] string] logType:@""];
		[self logMessage:@"\n" logType:@""];
	}
	
	// Clear the input window
	[inputView setString:@""];
}

- (IBAction)setModeClient:(id)sender
{
	if ([[displayName stringValue] compare:@"Server"] == NSOrderedSame)
	{
		[displayName setStringValue:@"Client"];
	}
}

- (IBAction)setModeServer:(id)sender
{
	if ([[displayName stringValue] compare:@"Client"] == NSOrderedSame)
	{
		[displayName setStringValue:@"Server"];
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
