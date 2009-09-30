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

- (id)init
{
	if(self = [super init])
		isRunning = NO;

	return self;
}

- (void)awakeFromNib
{	
	[logView setString:@""];
	[inputView setString:@""];
	[vigenereMult addItemsWithObjectValues:(NSArray *)[NSArray arrayWithObjects:
													   @"1",@"3",@"5",@"7",@"9",@"11",@"15",
													   @"17",@"19",@"21",@"23",@"25",nil]];
	
	for (int i = 0; i < 26; i++)
	{
		[vigenereAdd addItemWithObjectValue:(NSString *)[NSString stringWithFormat:@"%d", i]];
	}
	
	[vigenereMult selectItemAtIndex:1];
	[vigenereAdd selectItemAtIndex:7];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
}

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
	NSString *paragraph = [NSString stringWithFormat:@"%@\n", msg];
	
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
