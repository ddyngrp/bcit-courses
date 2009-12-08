/*-----------------------------------------------------------------------------
 * SOURCE FILE:	AppDelegate.m - Main delegate for the application
 * 
 * PROGRAM:     MacGPGTool
 * 
 * FUNCTIONS:   
 *            - (id)init
 *            - (void)awakeFromNib
 *            - (void)dealloc
 *            - (NSArray *)selectedRecipients
 *            - (IBAction)searchKeys:(id)sender
 *            - (int)numberOfRowsInTableView:(NSTableView *)tableView
 *            - (id)tableView:(NSTableView *)tableView
 *                   objectValueForTableColumn:(NSTableColumn *)
 *                   tableColumn row:(int)row
 *            - (void)tableViewSelectionDidChange:
 *                   (NSNotification *)notification
 *            - (BOOL)tableView:(NSTableView *)tv
 *                   writeRows:(NSArray*)rows
 *                   toPasteboard:(NSPasteboard*)pboard
 *            - (IBAction)ok:(id)sender
 *            - (IBAction)cancel:(id)sender
 *            - (NSString *)context:(GPGContext *)context
 *                   passphraseForKey:(GPGKey *)key again:(BOOL)again
 *            - (void)decryptFile:(NSString *)inputFilename
 *            - (IBAction)decrypt:(id)sender
 *            - (void)contextOperationIsProgressing:
 *                   (NSNotification *)notification
 *            - (IBAction)encrypt:(id)sender
 *            - (IBAction)askInputFileForEncryption:(id)sender
 *            - (IBAction)askOutputFileForEncryption:(id)sender
 *            - (BOOL)validateMenuItem:(NSMenuItem *)menuItem
 *            - (IBAction)askInputFileForSigning:(id)sender
 *            - (IBAction)askOutputFileForSigning:(id)sender
 *            - (IBAction)sign:(id)sender
 *            - (void)authenticateFile:(NSString *)inputFilename
 *                   againstSignatureFile:(NSString *)signatureFilename
 *            - (IBAction)verify:(id)sender
 *            - (IBAction)verifyDetachedSignature:(id)sender
 * 
 * DATE:        December 7, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * NOTES: This is the main delegate for the application. It handles all GUI
 *        and client/server functions. The application itself enables a user
 *        to search for GnuPG keys in their keyring as well as encrypt,
 *        decrypt, and sign files.
 *
 *---------------------------------------------------------------------------*/

#include "AppDelegate.h"

@implementation AppDelegate

/*-----------------------------------------------------------------------------
 * FUNCTION:    init
 * 
 * DATE:        December 7, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (id)init
 * 
 * RETURNS: The ID for the initialized class.
 * 
 * NOTES: Initializes the delegate class.
 *
 *----------------------------------------------------------------------------*/
- (id)init
{
	[super init];	
	return self;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    awakeFromNib
 * 
 * DATE:        December 7, 2009
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
 * NOTES: Once the application successfully loads, this section is executed.
 *        Prints out the available encryption engine(s) as well as details
 *        releating version number, key loactions, etc...
 *
 *----------------------------------------------------------------------------*/
- (void)awakeFromNib
{
	NSString	*aString;
	GPGContext	*aContext = [[GPGContext alloc] init];
	
	[[NSNotificationCenter defaultCenter] addObserver:self
											 selector:@selector(keyringChanged:)
												 name:GPGKeyringChangedNotification
											   object:nil];
	aString = [NSString stringWithFormat:@"Available engines:\n%@\nGroups:\n%@",
			   [[GPGEngine availableEngines] valueForKey:@"debugDescription"],
			   [[aContext keyGroups] valueForKey:@"name"]];
	[xmlTextView setString:aString];
	[aContext release];
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    dealloc
 * 
 * DATE:        December 7, 2009
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
 * NOTES: Cleans up on application termination.
 *
 *----------------------------------------------------------------------------*/
- (void)dealloc
{
	[[keyTableView window] release];
	[passphrasePanel release];
	[encryptionPanel release];
	[signingPanel release];
	[keys release];
	[selectedKeyUserIDsWithSignatures release];
	
	[super dealloc];
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    selectedRecipients
 * 
 * DATE:        December 7, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (NSArray *)selectedRecipients
 * 
 * RETURNS: NSArray of recipient keys.
 * 
 * NOTES: Returns a list of selected public keys.
 *
 *----------------------------------------------------------------------------*/
- (NSArray *)selectedRecipients
{
	if([keyTableView numberOfSelectedRows] <= 0)
		return nil;
	else {
		NSMutableArray	*recipients = [[NSMutableArray alloc] init];
		NSEnumerator	*anEnum = [keyTableView selectedRowEnumerator];
		NSNumber		*aRow;
		
		while(aRow = [anEnum nextObject]) {
			GPGKey	*aKey = [keys objectAtIndex:[aRow intValue]];
			
			[recipients addObject:aKey];
		}
		
		return [recipients autorelease];
	}
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    searchKeys
 * 
 * DATE:        December 7, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (IBAction)searchKeys:(id)sender
 * 
 * RETURNS: void
 * 
 * NOTES: Searches the local keyring in the "~/.gnupg" for keys that match
 *        the search parameters. If the search is blank, it returns all keys.
 *
 *----------------------------------------------------------------------------*/
- (IBAction)searchKeys:(id)sender
{
	GPGContext	*aContext = [[GPGContext alloc] init];
	
	[keys release];
	keys = nil;
	keys = [[[aContext keyEnumeratorForSearchPatterns:[NSArray arrayWithObject:[searchPatternTextField stringValue]]
									   secretKeysOnly:[secretKeySwitch state]] allObjects] retain];
	[aContext stopKeyEnumeration];
	[aContext release];
	[keyTableView noteNumberOfRowsChanged];
	[keyTableView reloadData];
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    numberOfRowsInTableView
 * 
 * DATE:        December 7, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (int)numberOfRowsInTableView:(NSTableView *)tableView
 * 
 * RETURNS: int of rows in a table
 * 
 * NOTES: Helper function to return the number of rows in a given table.
 *
 *----------------------------------------------------------------------------*/
- (int)numberOfRowsInTableView:(NSTableView *)tableView
{
	if(tableView == keyTableView)
		return [keys count];
	else {
		int	selectedRow = [keyTableView selectedRow];
		
		if(selectedRow >= 0) {
			GPGKey	*selectedKey = [keys objectAtIndex:selectedRow];
			
			return [[selectedKey subkeys] count];
		}
		else
			return 0;
	}
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    tableView
 * 
 * DATE:        December 7, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (id)tableView:(NSTableView *)tableView objectValueForTableColumn:(NSTableColumn *)tableColumn row:(int)row
 * 
 * RETURNS: The object ID of key in a NSTableView object.
 * 
 * NOTES: Returns the object ID for a specific key in the table.
 *
 *----------------------------------------------------------------------------*/
- (id)tableView:(NSTableView *)tableView objectValueForTableColumn:(NSTableColumn *)tableColumn row:(int)row
{
	return [[keys objectAtIndex:row] valueForKey:[tableColumn identifier]];
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    tableViewSelectionDidChange
 * 
 * DATE:        December 7, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (void)tableViewSelectionDidChange:(NSNotification *)notification
 * 
 * RETURNS: void
 * 
 * NOTES: Event notifier that the selection in the key table has changed. This
 *        then updates all relevant fields relating to the display of the
 *        key details. If nothing is selected, it sets default values.
 *
 *----------------------------------------------------------------------------*/
- (void)tableViewSelectionDidChange:(NSNotification *)notification
{
	if([notification object] == keyTableView) {
		int	selectedRow = [keyTableView selectedRow];
		
		if(selectedRow >= 0) {
			GPGKey			*selectedKey = [keys objectAtIndex:selectedRow];
			GPGContext		*aContext = [[GPGContext alloc] init];
			GPGTrustItem	*trustItem;
			
			[xmlTextView setString:[[selectedKey dictionaryRepresentation] description]];
			
			[mainKeyBox setTitle:[selectedKey userID]];
			
			[algorithmTextField setStringValue:[selectedKey algorithmDescription]];
			[lengthTextField setIntValue:[selectedKey length]];
			
			[hasSecretSwitch setState:[selectedKey isSecret]];
			[canExcryptSwitch setState:[selectedKey canEncrypt]];
			[canSignSwitch setState:[selectedKey canSign]];
			[canCertifySwitch setState:[selectedKey canCertify]];
			
			[isRevokedSwitch setState:[selectedKey isKeyRevoked]];
			[isInvalidSwitch setState:[selectedKey isKeyInvalid]];
			[hasExpiredSwitch setState:[selectedKey hasKeyExpired]];
			[isDisabledSwitch setState:[selectedKey isKeyDisabled]];
			
			trustItem = [[[aContext trustItemEnumeratorForSearchPattern:[selectedKey fingerprint]
														   maximumLevel:100] allObjects] lastObject];
			[aContext release];
		}
		else {
			[xmlTextView setString:@""];
			[mainKeyBox setTitle:@""];
			[algorithmTextField setStringValue:@""];
			[lengthTextField setIntValue:0];
			
			[hasSecretSwitch setState:NO];
			[canExcryptSwitch setState:NO];
			[canSignSwitch setState:NO];
			[canCertifySwitch setState:NO];
			
			[isRevokedSwitch setState:NO];
			[isInvalidSwitch setState:NO];
			[hasExpiredSwitch setState:NO];
			[isDisabledSwitch setState:NO];
		}
	}
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    tableView
 * 
 * DATE:        December 7, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (BOOL)tableView:(NSTableView *)tv writeRows:(NSArray*)rows toPasteboard:(NSPasteboard*)pboard
 * 
 * RETURNS: YES if the selected table was the key table.
 * 
 * NOTES: Copies the selected row in the key table to the clipboard.
 *
 *----------------------------------------------------------------------------*/
- (BOOL)tableView:(NSTableView *)tv writeRows:(NSArray*)rows toPasteboard:(NSPasteboard*)pboard
{
	if(tv == keyTableView && [rows count] == 1) {
		GPGContext	*aContext = [[GPGContext alloc] init];
		GPGData		*exportedKeyData;
		
		[pboard declareTypes:[NSArray arrayWithObjects:NSStringPboardType, nil] owner:nil];
		
		[aContext setUsesArmor:YES];
		exportedKeyData = [aContext exportedKeys:
						   [NSArray arrayWithObject:[keys objectAtIndex:[[rows lastObject] intValue]]]];
		[pboard setString:[exportedKeyData string] forType:NSStringPboardType];
		[aContext release];
		
		return YES;
	}
	
	return NO;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    ok
 * 
 * DATE:        December 7, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (IBAction)ok:(id)sender
 * 
 * RETURNS: void
 * 
 * NOTES: Helper function to confirm a dialogue boxes when "OK" is pressed.
 *
 *----------------------------------------------------------------------------*/
- (IBAction)ok:(id)sender
{
	[[sender window] orderOut:sender];
	[NSApp stopModalWithCode:NSAlertDefaultReturn];
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    cancel
 * 
 * DATE:        December 7, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (IBAction)cancel:(id)sender
 * 
 * RETURNS: void
 * 
 * NOTES: Helper function to dismiss a dialogue when "Cancel" is pressed.
 *
 *----------------------------------------------------------------------------*/
- (IBAction)cancel:(id)sender
{
	[[sender window] orderOut:sender];
	[NSApp stopModalWithCode:NSAlertAlternateReturn];
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    context
 * 
 * DATE:        December 7, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (NSString *)context:(GPGContext *)context passphraseForKey:(GPGKey *)key again:(BOOL)again
 * 
 * RETURNS: NSString of the passphrase
 * 
 * NOTES: Returns the entered passphrase used to encrypt, decrypt, or sign.
 *
 *----------------------------------------------------------------------------*/
- (NSString *)context:(GPGContext *)context passphraseForKey:(GPGKey *)key again:(BOOL)again
{
	if(key == nil)
		[passphraseDescriptionTextField setStringValue:
		 @"Symetric encryption: enter a passphrase (no key is used)"];
	else
		[passphraseDescriptionTextField setStringValue:[key userID]];
	[passphraseTextField setStringValue:@""];
	[passphrasePanel orderFront:nil];
	
	if([NSApp runModalForWindow:passphrasePanel] == NSAlertDefaultReturn) {
		NSString	*passphrase = [[passphraseTextField stringValue] copy];
		
		[passphraseTextField setStringValue:@""];
		return [passphrase autorelease];
	}
	else
		return nil;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    decryptFile
 * 
 * DATE:        December 7, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (void)decryptFile:(NSString *)inputFilename
 * 
 * RETURNS: void
 * 
 * NOTES: Attempts to decrypt a given file. Has an exception handler in case
 *        the file is of incorrect format.
 *
 *----------------------------------------------------------------------------*/
- (void)decryptFile:(NSString *)inputFilename
{
	GPGContext			*aContext = [[GPGContext alloc] init];
	volatile GPGData	*decryptedData = nil, *inputData = nil;
	NSSavePanel			*savePanel;
	
	[aContext setPassphraseDelegate:self];
	[[NSNotificationCenter defaultCenter] addObserver:self
											 selector:@selector(contextOperationIsProgressing:)
												 name:GPGProgressNotification
											   object:aContext];
	
	NS_DURING
		inputData = [[GPGData alloc] initWithContentsOfFile:inputFilename];
		
		decryptedData = [[aContext decryptedData:(GPGData *)inputData] retain];
		
		[(GPGData *)inputData release];
		NSLog(@"Keys used for encryption: %@", [[[aContext operationResults] objectForKey:@"keyErrors"] allKeys]);
	NS_HANDLER
		NSLog(@"Exception userInfo: %@", [localException userInfo]);
		NSRunAlertPanel(@"Error", @"%@", nil, nil, nil, [localException reason]);
		[aContext release];
		[(GPGData *)inputData release];
		[(GPGData *)decryptedData release];
		return;
	NS_ENDHANDLER
	
	savePanel = [NSSavePanel savePanel];
	[savePanel setTreatsFilePackagesAsDirectories:YES];
	
	if([savePanel runModalForDirectory:nil file:[decryptedData filename]] == NSOKButton) {
		[[(GPGData *)decryptedData data] writeToFile:[savePanel filename] atomically:NO];
	}
	[[NSNotificationCenter defaultCenter] removeObserver:self
													name:GPGProgressNotification
												  object:aContext];
	[aContext release];
	[(GPGData *)decryptedData release];
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    decrypt
 * 
 * DATE:        December 7, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (IBAction)decrypt:(id)sender
 * 
 * RETURNS: void
 * 
 * NOTES: Opens a dialogue box to select a file to decrypt.
 *
 *----------------------------------------------------------------------------*/
- (IBAction)decrypt:(id)sender
{
	NSOpenPanel	*openPanel = [NSOpenPanel openPanel];
	
	[openPanel setAllowsMultipleSelection:NO];
	[openPanel setCanChooseDirectories:NO];
	[openPanel setCanChooseFiles:YES];
	[openPanel setAllowsMultipleSelection:NO];
	[openPanel setTreatsFilePackagesAsDirectories:YES];
	
	if([openPanel runModalForTypes:nil] == NSOKButton) {
		[self decryptFile:[openPanel filename]];
	}
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    contextOperationIsProgressing
 * 
 * DATE:        December 7, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (void)contextOperationIsProgressing:(NSNotification *)notification
 * 
 * RETURNS: void
 * 
 * NOTES: Event notification for the selection of user info for specific keys.
 *
 *----------------------------------------------------------------------------*/
- (void)contextOperationIsProgressing:(NSNotification *)notification
{
	NSDictionary	*userInfo = [notification userInfo];
	
	NSLog(@"%@ (%@): %@/%@", [userInfo objectForKey:@"description"],
		  [userInfo objectForKey:@"type"],
		  [userInfo objectForKey:@"current"],
		  [userInfo objectForKey:@"total"]);
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    encrypt
 * 
 * DATE:        December 7, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (IBAction)encrypt:(id)sender
 * 
 * RETURNS: void
 * 
 * NOTES: Encrypts a given file. Also has an exception handler.
 *
 *----------------------------------------------------------------------------*/
- (IBAction)encrypt:(id)sender
{
	if([NSApp runModalForWindow:encryptionPanel] == NSOKButton) {
		GPGContext			*aContext;
		GPGData				*inputData;
		volatile GPGData	*outputData;
		NSString            *filePath = [encryptionInputFilenameTextField stringValue];
		
		if([filePath length] == 0 || [[encryptionOutputFilenameTextField stringValue] length] == 0) {
			NSRunAlertPanel(@"Error", @"You need to give a filename for input and output files.",
							nil, nil, nil);
			return;
		}
		
		aContext = [[GPGContext alloc] init];
		[aContext setUsesArmor:[encryptionArmoredSwitch state]];
		inputData = [[GPGData alloc] initWithContentsOfFile:filePath];
		
		NS_DURING
			NSArray	*selectedRecipients = [self selectedRecipients];
			
			if(selectedRecipients != nil)
				outputData = [aContext encryptedData:inputData
											withKeys:[self selectedRecipients]
										trustAllKeys:[trustSwitch state]];
			else {
				// Symmetric encryption
				[aContext setPassphraseDelegate:self];
				outputData = [aContext encryptedData:inputData];
			}
		NS_HANDLER
			outputData = nil;
			NSLog(@"Exception userInfo: %@", [localException userInfo]);
			NSLog(@"Operation results: %@", [[[localException userInfo] objectForKey:GPGContextKey] operationResults]);
			NSRunAlertPanel(@"Error", @"%@", nil, nil, nil, [localException reason]);
		NS_ENDHANDLER
		
		if(outputData != nil) {
			[[(GPGData *)outputData data] writeToFile:[encryptionOutputFilenameTextField stringValue] atomically:NO];
		}
		[inputData release];
		[aContext release];
	}
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    askInputFileForEncryption
 * 
 * DATE:        December 7, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (IBAction)askInputFileForEncryption:(id)sender
 * 
 * RETURNS: void
 * 
 * NOTES: Prompts the user for an input file to be encrypted.
 *
 *----------------------------------------------------------------------------*/
- (IBAction)askInputFileForEncryption:(id)sender
{
	NSOpenPanel	*openPanel = [NSOpenPanel openPanel];
	
	[openPanel setAllowsMultipleSelection:NO];
	[openPanel setCanChooseDirectories:NO];
	[openPanel setCanChooseFiles:YES];
	[openPanel setAllowsMultipleSelection:NO];
	[openPanel setTreatsFilePackagesAsDirectories:YES];
	
	if([openPanel runModalForTypes:nil] == NSOKButton) {
		[encryptionInputFilenameTextField setStringValue:[openPanel filename]];
	}
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    askOutputFileForEncryption
 * 
 * DATE:        December 7, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (IBAction)askOutputFileForEncryption:(id)sender
 * 
 * RETURNS: void
 * 
 * NOTES: Prompts the user to enter a name for the resultant encrypted file.
 *
 *----------------------------------------------------------------------------*/
- (IBAction)askOutputFileForEncryption:(id)sender
{
	NSSavePanel	*savePanel = [NSSavePanel savePanel];
	
	[savePanel setTreatsFilePackagesAsDirectories:YES];
	
	if([savePanel runModal] == NSOKButton) {
		[encryptionOutputFilenameTextField setStringValue:[savePanel filename]];
	}
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    validateMenuItem
 * 
 * DATE:        December 7, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (BOOL)validateMenuItem:(NSMenuItem *)menuItem
 * 
 * RETURNS: YES if the menu option selected is valid.
 * 
 * NOTES: Returns YES if the selected menu item is valid and the user has
 *        selected a key from the table.
 *
 *----------------------------------------------------------------------------*/
- (BOOL)validateMenuItem:(NSMenuItem *)menuItem
{
	if([menuItem action] == @selector(sign:))
		return [keyTableView numberOfSelectedRows] > 0;
	else
		return YES;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    askInputFileForSigning
 * 
 * DATE:        December 7, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (IBAction)askInputFileForSigning:(id)sender
 * 
 * RETURNS: void
 * 
 * NOTES: Promt the user for an input file to sign.
 *
 *----------------------------------------------------------------------------*/
- (IBAction)askInputFileForSigning:(id)sender
{
	NSOpenPanel	*openPanel = [NSOpenPanel openPanel];
	
	[openPanel setAllowsMultipleSelection:NO];
	[openPanel setCanChooseDirectories:NO];
	[openPanel setCanChooseFiles:YES];
	[openPanel setAllowsMultipleSelection:NO];
	[openPanel setTreatsFilePackagesAsDirectories:YES];
	
	if([openPanel runModalForTypes:nil] == NSOKButton) {
		[signingInputFilenameTextField setStringValue:[openPanel filename]];
	}
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    askOutputFileForSigning
 * 
 * DATE:        December 7, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (IBAction)askOutputFileForSigning:(id)sender
 * 
 * RETURNS: void
 * 
 * NOTES: Promt the user for the name of the resulting signed file.
 *
 *----------------------------------------------------------------------------*/
- (IBAction)askOutputFileForSigning:(id)sender
{
	NSSavePanel	*savePanel = [NSSavePanel savePanel];
	
	[savePanel setTreatsFilePackagesAsDirectories:YES];
	
	if([savePanel runModal] == NSOKButton) {
		[signingOutputFilenameTextField setStringValue:[savePanel filename]];
	}
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    sign
 * 
 * DATE:        December 7, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (IBAction)sign:(id)sender
 * 
 * RETURNS: void
 * 
 * NOTES: Initiates the digital signing of a file using a selected GnuPG key.
 *
 *----------------------------------------------------------------------------*/
- (IBAction)sign:(id)sender
{
	if([NSApp runModalForWindow:signingPanel] == NSOKButton) {
		GPGContext			*aContext;
		GPGData				*inputData;
		volatile GPGData	*outputData = nil;
		
		if([[signingInputFilenameTextField stringValue] length] == 0
		   || [[signingOutputFilenameTextField stringValue] length] == 0) {
			NSRunAlertPanel(@"Error", @"You need to give a filename for input and output files.", nil, nil, nil);
			return;
		}
		
		aContext = [[GPGContext alloc] init];
		[aContext setPassphraseDelegate:self];
		[[NSNotificationCenter defaultCenter] addObserver:self
												 selector:@selector(contextOperationIsProgressing:)
													 name:GPGProgressNotification
												   object:aContext];
		[aContext setUsesArmor:[signingArmoredSwitch state]];
		inputData = [[GPGData alloc] initWithContentsOfFile:[signingInputFilenameTextField stringValue]];
		
		NS_DURING
			NSEnumerator	*anEnum = [keyTableView selectedRowEnumerator];
			NSNumber		*aRow;
			
			while(aRow = [anEnum nextObject])
				[aContext addSignerKey:[keys objectAtIndex:[aRow intValue]]];
			
			[aContext addSignatureNotationWithName:@"me@TEST_HUMAN_READABLE_NOTATION"
											 value:@"My human-readable notation"
											 flags:GPGSignatureNotationCriticalMask];
			[aContext addSignatureNotationWithName:nil value:@"http://macgpg.sf.net/" flags:0];
			outputData = [aContext signedData:inputData signatureMode:[signingDetachedSwitch state]];
		NS_HANDLER
			outputData = nil;
			NSLog(@"Exception userInfo: %@", [localException userInfo]);
			NSRunAlertPanel(@"Error", @"%@", nil, nil, nil, [localException reason]);
		NS_ENDHANDLER
		
		if(outputData != nil) {
			[[(GPGData *)outputData data] writeToFile:[signingOutputFilenameTextField stringValue] atomically:NO];
		}
		[[NSNotificationCenter defaultCenter] removeObserver:self name:GPGProgressNotification object:aContext];
		[inputData release];
		[aContext release];
	}
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    authenticateFile
 * 
 * DATE:        December 7, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (void)authenticateFile:(NSString *)inputFilename againstSignatureFile:(NSString *)signatureFilename
 * 
 * RETURNS: void
 * 
 * NOTES: Authenticates a file that was signed using GnuPG against a signature.
 *
 *----------------------------------------------------------------------------*/
- (void)authenticateFile:(NSString *)inputFilename againstSignatureFile:(NSString *)signatureFilename
{
	GPGContext			*aContext = [[GPGContext alloc] init];
	volatile GPGData	*inputData = nil, *signatureData = nil;
	
	[[NSNotificationCenter defaultCenter] addObserver:self
											 selector:@selector(contextOperationIsProgressing:)
												 name:GPGProgressNotification
											   object:aContext];
	NS_DURING
		NSArray		*signatures;
		NSString	*statusString = nil;
		
		inputData = [[GPGData alloc] initWithContentsOfFile:inputFilename];
		if(signatureFilename != nil)
			signatureData = [[GPGData alloc] initWithContentsOfFile:signatureFilename];
		if(signatureData != nil)
			signatures = [aContext verifySignatureData:(GPGData *)signatureData
										   againstData:(GPGData *)inputData];
		else
			signatures = [aContext verifySignedData:(GPGData *)inputData];
		statusString = @"Signatures";
		NSLog(@"operation results = %@", [aContext operationResults]);
		
		NSEnumerator	*anEnum = [[aContext signatures] objectEnumerator];
		GPGSignature	*aSig;
		
		while(aSig = [anEnum nextObject]) {
			GPGKey	*signerKey = [aContext keyFromFingerprint:[aSig fingerprint] secretKey:NO];
			
			statusString = [statusString stringByAppendingFormat:@"\nStatus: %@,  \
							Summary: 0x%04x, Signer: %@, Signature Date: %@, \
							Expiration Date: %@, Validity: %@, Validity Error: %@, \
							Notations/Policy URLs: %@", GPGErrorDescription([aSig status]),
							[aSig summary], (signerKey ? [signerKey userID]:[aSig fingerprint]),
							[aSig creationDate], [aSig expirationDate], [aSig validityDescription],
							GPGErrorDescription([aSig validityError]), [aSig signatureNotations]];
		}
		
		NSLog(@"Signature notations/policies = %@", [aContext signatureNotations]);
		NSRunInformationalAlertPanel(@"Authentication result", statusString, nil, nil, nil);
		
	NS_HANDLER
		NSString		*statusString = @"Signatures";
		BOOL			hasSigs = NO;
		NSEnumerator	*anEnum = [[aContext signatures] objectEnumerator];
		GPGSignature	*aSig;
		
		NSLog(@"Exception userInfo: %@", [localException userInfo]);
		
		while(aSig = [anEnum nextObject]) {
			GPGKey	*signerKey = [aContext keyFromFingerprint:[aSig fingerprint] secretKey:NO];
			
			hasSigs = YES;
			statusString = [statusString stringByAppendingFormat:@"\nStatus: %@,  \
							Summary: 0x%04x, Signer: %@, Signature Date: %@, \
							Expiration Date: %@, Validity: %@, Validity Error: %@, \
							Notations: %@, Policy URLs: %@", GPGErrorDescription([aSig status]),
							[aSig summary], (signerKey ? [signerKey userID]:[aSig fingerprint]),
							[aSig creationDate], [aSig expirationDate], [aSig validityDescription],
							GPGErrorDescription([aSig validityError]), [aSig notations], [aSig policyURLs]];
		}
		
		if(hasSigs)
			NSRunInformationalAlertPanel(@"Authentication result", statusString, nil, nil, nil);
		else
			NSRunAlertPanel(@"Error", @"%@", nil, nil, nil, [localException reason]);
	NS_ENDHANDLER
	
	[[NSNotificationCenter defaultCenter] removeObserver:self name:GPGProgressNotification object:aContext];
	[aContext release];
	[(GPGData *)inputData release];
	[(GPGData *)signatureData release];
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    verify
 * 
 * DATE:        December 7, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (IBAction)verify:(id)sender
 * 
 * RETURNS: void
 * 
 * NOTES: Initiates verification of a signature.
 *
 *----------------------------------------------------------------------------*/
- (IBAction)verify:(id)sender
{
	NSOpenPanel	*openPanel = [NSOpenPanel openPanel];
	
	[openPanel setAllowsMultipleSelection:NO];
	[openPanel setCanChooseDirectories:NO];
	[openPanel setCanChooseFiles:YES];
	[openPanel setAllowsMultipleSelection:NO];
	[openPanel setTreatsFilePackagesAsDirectories:YES];
	
	if([openPanel runModalForTypes:nil] == NSOKButton) {
		[self authenticateFile:[openPanel filename] againstSignatureFile:nil];
	}
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    verifyDetachedSignature
 * 
 * DATE:        December 7, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (IBAction)verifyDetachedSignature:(id)sender
 * 
 * RETURNS: void
 * 
 * NOTES: Verifies a detached signature (a signature on its own).
 *
 *----------------------------------------------------------------------------*/
- (IBAction)verifyDetachedSignature:(id)sender
{
	NSOpenPanel	*openPanel = [NSOpenPanel openPanel];
	
	[openPanel setAllowsMultipleSelection:NO];
	[openPanel setCanChooseDirectories:NO];
	[openPanel setCanChooseFiles:YES];
	[openPanel setAllowsMultipleSelection:NO];
	[openPanel setTreatsFilePackagesAsDirectories:YES];
	
	if([openPanel runModalForTypes:nil] == NSOKButton) {
		NSString	*inputFilename = [[openPanel filename] copy];
		
		[openPanel setPrompt:@"Signature:"];
		
		if([openPanel runModalForTypes:nil] == NSOKButton) {
			[self authenticateFile:inputFilename againstSignatureFile:[openPanel filename]];
		}
		[inputFilename release];
	}
}

@end