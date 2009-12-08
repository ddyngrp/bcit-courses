#include "AppDelegate.h"

@interface AppDelegate(Private)
+ (GPGContext *) keySignatureBrowserContext;
+ (NSMutableDictionary *) signerPerUserIDCache;
- (void) reloadSelectedKeyUserIDsWithSignaturesFromKey:(GPGKey *)key;
@end

@implementation AppDelegate

- (id)init
{
	[super init];	
	return self;
}

- (void) awakeFromNib
{
    NSString	*aString;
    GPGContext	*aContext = [[GPGContext alloc] init];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyringChanged:) name:GPGKeyringChangedNotification object:nil];
    aString = [NSString stringWithFormat:@"Available engines:\n%@\nGroups:\n%@", [[GPGEngine availableEngines] valueForKey:@"debugDescription"], [[aContext keyGroups] valueForKey:@"name"]];
    [xmlTextView setString:aString];
    [aContext release];
}

- (void) dealloc
{
    [[keyTableView window] release];
    [passphrasePanel release];
    [encryptionPanel release];
    [signingPanel release];
    [keys release];
    [selectedKeyUserIDsWithSignatures release];
    
    [super dealloc];
}

- (NSArray *) selectedRecipients
{
    if([keyTableView numberOfSelectedRows] <= 0)
        return nil;
    else{
        NSMutableArray	*recipients = [[NSMutableArray alloc] init];
        NSEnumerator	*anEnum = [keyTableView selectedRowEnumerator];
        NSNumber		*aRow;
		
        while(aRow = [anEnum nextObject]){
            GPGKey	*aKey = [keys objectAtIndex:[aRow intValue]];
			
            [recipients addObject:aKey];
        }
		
        return [recipients autorelease];
    }
}

- (IBAction) searchKeys:(id)sender
{
    GPGContext	*aContext = [[GPGContext alloc] init];
    
    [keys release];
    keys = nil;
    keys = [[[aContext keyEnumeratorForSearchPatterns:[NSArray arrayWithObject:[searchPatternTextField stringValue]] secretKeysOnly:[secretKeySwitch state]] allObjects] retain];
    [aContext stopKeyEnumeration];
    [aContext release];
    [keyTableView noteNumberOfRowsChanged];
    [keyTableView reloadData];
}

- (id) outlineView:(NSOutlineView *)outlineView child:(int)index ofItem:(id)item
{
	return [[item userIDs] objectAtIndex:index];
}

- (BOOL) outlineView:(NSOutlineView *)outlineView isItemExpandable:(id)item
{
    return [item isKindOfClass:[GPGKey class]];
}

- (int) numberOfRowsInTableView:(NSTableView *)tableView
{
    if(tableView == keyTableView)
        return [keys count];
    else{
        int	selectedRow = [keyTableView selectedRow];
		
        if(selectedRow >= 0){
            GPGKey	*selectedKey = [keys objectAtIndex:selectedRow];
			
            if(tableView == userIDTableView)
                return [[selectedKey userIDs] count];
            else /* subkeyTableView */
                return [[selectedKey subkeys] count];
        }
        else
            return 0;
    }
}

- (id) tableView:(NSTableView *)tableView objectValueForTableColumn:(NSTableColumn *)tableColumn row:(int)row
{
    id	rowObject = nil;
    
    if(tableView == keyTableView)
        rowObject = [keys objectAtIndex:row];
    else{
        GPGKey	*selectedKey = [keys objectAtIndex:[keyTableView selectedRow]];
        
        if(tableView == userIDTableView)
            rowObject = [[selectedKey userIDs] objectAtIndex:row];
        else
            rowObject = [[selectedKey subkeys] objectAtIndex:row];
    }
    return [rowObject valueForKey:[tableColumn identifier]];
}

- (void) tableViewSelectionDidChange:(NSNotification *)notification
{
    if([notification object] == keyTableView){
        int	selectedRow = [keyTableView selectedRow];
        
        if(selectedRow >= 0){
            GPGKey			*selectedKey = [keys objectAtIndex:selectedRow];
            GPGContext		*aContext = [[GPGContext alloc] init];
            GPGTrustItem	*trustItem;
			
            [xmlTextView setString:[[selectedKey dictionaryRepresentation] description]];
			
            [mainKeyBox setTitle:[selectedKey userID]];
			
            [algorithmTextField setStringValue:[selectedKey algorithmDescription]];
            [lengthTextField setIntValue:[selectedKey length]];
            [validityTextField setIntValue:[selectedKey validity]];
			
            [hasSecretSwitch setState:[selectedKey isSecret]];
            [canExcryptSwitch setState:[selectedKey canEncrypt]];
            [canSignSwitch setState:[selectedKey canSign]];
            [canCertifySwitch setState:[selectedKey canCertify]];
			
            [isRevokedSwitch setState:[selectedKey isKeyRevoked]];
            [isInvalidSwitch setState:[selectedKey isKeyInvalid]];
            [hasExpiredSwitch setState:[selectedKey hasKeyExpired]];
            [isDisabledSwitch setState:[selectedKey isKeyDisabled]];
			
            trustItem = [[[aContext trustItemEnumeratorForSearchPattern:[selectedKey fingerprint] maximumLevel:100] allObjects] lastObject];
            [aContext release];
			
            [self reloadSelectedKeyUserIDsWithSignaturesFromKey:selectedKey];
        }
        else{
            [xmlTextView setString:@""];
            [mainKeyBox setTitle:@""];
            [algorithmTextField setStringValue:@""];
            [lengthTextField setIntValue:0];
            [validityTextField setIntValue:0];
			
            [hasSecretSwitch setState:NO];
            [canExcryptSwitch setState:NO];
            [canSignSwitch setState:NO];
            [canCertifySwitch setState:NO];
			
            [isRevokedSwitch setState:NO];
            [isInvalidSwitch setState:NO];
            [hasExpiredSwitch setState:NO];
            [isDisabledSwitch setState:NO];
        }
        [subkeyTableView noteNumberOfRowsChanged];
        [subkeyTableView reloadData];
        [userIDTableView noteNumberOfRowsChanged];
        [userIDTableView reloadData];
    }
}

- (BOOL)tableView:(NSTableView *)tv writeRows:(NSArray*)rows toPasteboard:(NSPasteboard*)pboard
{
    if(tv == keyTableView && [rows count] == 1){
        GPGContext	*aContext = [[GPGContext alloc] init];
        GPGData		*exportedKeyData;
		
        [pboard declareTypes:[NSArray arrayWithObjects:/*@"application/pgp-keys",*/ NSStringPboardType/*, NSFileContentsPboardType*/, nil] owner:nil];
		
        [aContext setUsesArmor:YES];
        exportedKeyData = [aContext exportedKeys:[NSArray arrayWithObject:[keys objectAtIndex:[[rows lastObject] intValue]]]];
        [pboard setString:[exportedKeyData string] forType:NSStringPboardType];
        [aContext release];
		
        return YES;
    }
	
    return NO;
}
- (NSDragOperation)tableView:(NSTableView*)tv validateDrop:(id <NSDraggingInfo>)info proposedRow:(int)row proposedDropOperation:(NSTableViewDropOperation)op
{
    return NSDragOperationNone;
}

- (IBAction) ok:(id)sender
{
    [[sender window] orderOut:sender];
    [NSApp stopModalWithCode:NSAlertDefaultReturn];
}

- (IBAction) cancel:(id)sender
{
    [[sender window] orderOut:sender];
    [NSApp stopModalWithCode:NSAlertAlternateReturn];
}

- (NSString *) context:(GPGContext *)context passphraseForKey:(GPGKey *)key again:(BOOL)again
{
    if(key == nil)
        [passphraseDescriptionTextField setStringValue:@"Symetric encryption: enter a passphrase (no key is used)"];
    else
        [passphraseDescriptionTextField setStringValue:[key userID]];
    [passphraseTextField setStringValue:@""];
    [passphrasePanel orderFront:nil];
	
    if([NSApp runModalForWindow:passphrasePanel] == NSAlertDefaultReturn){
        NSString	*passphrase = [[passphraseTextField stringValue] copy];
		
        [passphraseTextField setStringValue:@""];
        return [passphrase autorelease];
    }
    else
        return nil;
}

- (void) decryptFile:(NSString *)inputFilename
{
    GPGContext			*aContext = [[GPGContext alloc] init];
    volatile GPGData	*decryptedData = nil, *inputData = nil;
    NSSavePanel			*savePanel;
	
    [aContext setPassphraseDelegate:self];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(contextOperationIsProgressing:) name:GPGProgressNotification object:aContext];
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
	
    if([savePanel runModalForDirectory:nil file:[decryptedData filename]] == NSOKButton){
        [[(GPGData *)decryptedData data] writeToFile:[savePanel filename] atomically:NO];
    }
    [[NSNotificationCenter defaultCenter] removeObserver:self name:GPGProgressNotification object:aContext];
    [aContext release];
    [(GPGData *)decryptedData release];
}

- (IBAction) decrypt:(id)sender
{
    NSOpenPanel	*openPanel = [NSOpenPanel openPanel];
	
    [openPanel setAllowsMultipleSelection:NO];
    [openPanel setCanChooseDirectories:NO];
    [openPanel setCanChooseFiles:YES];
    [openPanel setAllowsMultipleSelection:NO];
    [openPanel setTreatsFilePackagesAsDirectories:YES];
	
    if([openPanel runModalForTypes:nil] == NSOKButton){
        [self decryptFile:[openPanel filename]];
    }
}

- (void) contextOperationIsProgressing:(NSNotification *)notification
{
    NSDictionary	*userInfo = [notification userInfo];
    
    NSLog(@"%@ (%@): %@/%@", [userInfo objectForKey:@"description"], [userInfo objectForKey:@"type"], [userInfo objectForKey:@"current"], [userInfo objectForKey:@"total"]);
}

- (IBAction) encrypt:(id)sender
{
    if([NSApp runModalForWindow:encryptionPanel] == NSOKButton){
        GPGContext			*aContext;
        GPGData				*inputData;
        volatile GPGData	*outputData;
        NSString            *filePath = [encryptionInputFilenameTextField stringValue];
		
        if([filePath length] == 0 || [[encryptionOutputFilenameTextField stringValue] length] == 0){
            NSRunAlertPanel(@"Error", @"You need to give a filename for input and output files.", nil, nil, nil);
            return;
        }
		
        aContext = [[GPGContext alloc] init];
        [aContext setUsesArmor:[encryptionArmoredSwitch state]];
        inputData = [[GPGData alloc] initWithContentsOfFile:filePath];
		
        NS_DURING
		NSArray	*selectedRecipients = [self selectedRecipients];
		
		if(selectedRecipients != nil)
			outputData = [aContext encryptedData:inputData withKeys:[self selectedRecipients] trustAllKeys:[trustSwitch state]];
		else{
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
		
        if(outputData != nil){
            [[(GPGData *)outputData data] writeToFile:[encryptionOutputFilenameTextField stringValue] atomically:NO];
        }
        [inputData release];
        [aContext release];
    }
}

- (IBAction) askInputFileForEncryption:(id)sender
{
    NSOpenPanel	*openPanel = [NSOpenPanel openPanel];
	
    [openPanel setAllowsMultipleSelection:NO];
    [openPanel setCanChooseDirectories:NO];
    [openPanel setCanChooseFiles:YES];
    [openPanel setAllowsMultipleSelection:NO];
    [openPanel setTreatsFilePackagesAsDirectories:YES];
	
    if([openPanel runModalForTypes:nil] == NSOKButton){
        [encryptionInputFilenameTextField setStringValue:[openPanel filename]];
    }
}

- (IBAction) askOutputFileForEncryption:(id)sender
{
    NSSavePanel	*savePanel = [NSSavePanel savePanel];
    
    [savePanel setTreatsFilePackagesAsDirectories:YES];
	
    if([savePanel runModal] == NSOKButton){
        [encryptionOutputFilenameTextField setStringValue:[savePanel filename]];
    }
}

- (BOOL) validateMenuItem:(NSMenuItem *)menuItem
{
    if([menuItem action] == @selector(encrypt:) || [menuItem action] == @selector(sign:))
        return [keyTableView numberOfSelectedRows] > 0;
    else
        return YES;
}

- (IBAction) askInputFileForSigning:(id)sender
{
    NSOpenPanel	*openPanel = [NSOpenPanel openPanel];
	
    [openPanel setAllowsMultipleSelection:NO];
    [openPanel setCanChooseDirectories:NO];
    [openPanel setCanChooseFiles:YES];
    [openPanel setAllowsMultipleSelection:NO];
    [openPanel setTreatsFilePackagesAsDirectories:YES];
	
    if([openPanel runModalForTypes:nil] == NSOKButton){
        [signingInputFilenameTextField setStringValue:[openPanel filename]];
    }
}

- (IBAction) askOutputFileForSigning:(id)sender
{
    NSSavePanel	*savePanel = [NSSavePanel savePanel];
	
    [savePanel setTreatsFilePackagesAsDirectories:YES];
	
    if([savePanel runModal] == NSOKButton){
        [signingOutputFilenameTextField setStringValue:[savePanel filename]];
    }
}

- (IBAction) sign:(id)sender
{
    if([NSApp runModalForWindow:signingPanel] == NSOKButton){
        GPGContext			*aContext;
        GPGData				*inputData;
        volatile GPGData	*outputData = nil;
		
        if([[signingInputFilenameTextField stringValue] length] == 0 || [[signingOutputFilenameTextField stringValue] length] == 0){
            NSRunAlertPanel(@"Error", @"You need to give a filename for input and output files.", nil, nil, nil);
            return;
        }
		
        aContext = [[GPGContext alloc] init];
        [aContext setPassphraseDelegate:self];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(contextOperationIsProgressing:) name:GPGProgressNotification object:aContext];
        [aContext setUsesArmor:[signingArmoredSwitch state]];
        inputData = [[GPGData alloc] initWithContentsOfFile:[signingInputFilenameTextField stringValue]];
		
        NS_DURING
		NSEnumerator	*anEnum = [keyTableView selectedRowEnumerator];
		NSNumber		*aRow;
		
		while(aRow = [anEnum nextObject])
			[aContext addSignerKey:[keys objectAtIndex:[aRow intValue]]];
		
		[aContext addSignatureNotationWithName:@"me@TEST_HUMAN_READABLE_NOTATION" value:@"My human-readable notation" flags:GPGSignatureNotationCriticalMask];
		[aContext addSignatureNotationWithName:nil value:@"http://macgpg.sf.net/" flags:0];
		outputData = [aContext signedData:inputData signatureMode:[signingDetachedSwitch state]];
        NS_HANDLER
		outputData = nil;
		NSLog(@"Exception userInfo: %@", [localException userInfo]);
		NSRunAlertPanel(@"Error", @"%@", nil, nil, nil, [localException reason]);
        NS_ENDHANDLER
		
        if(outputData != nil){
            [[(GPGData *)outputData data] writeToFile:[signingOutputFilenameTextField stringValue] atomically:NO];
        }
        [[NSNotificationCenter defaultCenter] removeObserver:self name:GPGProgressNotification object:aContext];
        [inputData release];
        [aContext release];
    }
}

- (NSString *) stringFromSignatureStatus:(GPGError)status
{
    return GPGErrorDescription(status);
}

- (void) authenticateFile:(NSString *)inputFilename againstSignatureFile:(NSString *)signatureFilename
{
    GPGContext			*aContext = [[GPGContext alloc] init];
    volatile GPGData	*inputData = nil, *signatureData = nil;
	
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(contextOperationIsProgressing:) name:GPGProgressNotification object:aContext];
    NS_DURING
	NSArray		*signatures;
	NSString	*statusString = nil;
	
	inputData = [[GPGData alloc] initWithContentsOfFile:inputFilename];
	if(signatureFilename != nil)
		signatureData = [[GPGData alloc] initWithContentsOfFile:signatureFilename];
	if(signatureData != nil)
		signatures = [aContext verifySignatureData:(GPGData *)signatureData againstData:(GPGData *)inputData];
	else
		signatures = [aContext verifySignedData:(GPGData *)inputData];
	statusString = @"Signatures";
	NSLog(@"operation results = %@", [aContext operationResults]);
	{
		NSEnumerator	*anEnum = [[aContext signatures] objectEnumerator];
		GPGSignature	*aSig;
		
		while(aSig = [anEnum nextObject]){
			GPGKey	*signerKey = [aContext keyFromFingerprint:[aSig fingerprint] secretKey:NO];
			
			statusString = [statusString stringByAppendingFormat:@"\nStatus: %@,  Summary: 0x%04x, Signer: %@, Signature Date: %@, Expiration Date: %@, Validity: %@, Validity Error: %@, Notations/Policy URLs: %@", GPGErrorDescription([aSig status]), [aSig summary], (signerKey ? [signerKey userID]:[aSig fingerprint]), [aSig creationDate], [aSig expirationDate], [aSig validityDescription], GPGErrorDescription([aSig validityError]), [aSig signatureNotations]];
		}
	}
	NSLog(@"Signature notations/policies = %@", [aContext signatureNotations]);
	NSRunInformationalAlertPanel(@"Authentication result", statusString, nil, nil, nil);
    NS_HANDLER
	NSString		*statusString = @"Signatures";
	BOOL			hasSigs = NO;
	NSEnumerator	*anEnum = [[aContext signatures] objectEnumerator];
	GPGSignature	*aSig;
	
	NSLog(@"Exception userInfo: %@", [localException userInfo]);
	
	while(aSig = [anEnum nextObject]){
		GPGKey	*signerKey = [aContext keyFromFingerprint:[aSig fingerprint] secretKey:NO];
		
		hasSigs = YES;
		statusString = [statusString stringByAppendingFormat:@"\nStatus: %@,  Summary: 0x%04x, Signer: %@, Signature Date: %@, Expiration Date: %@, Validity: %@, Validity Error: %@, Notations: %@, Policy URLs: %@", GPGErrorDescription([aSig status]), [aSig summary], (signerKey ? [signerKey userID]:[aSig fingerprint]), [aSig creationDate], [aSig expirationDate], [aSig validityDescription], GPGErrorDescription([aSig validityError]), [aSig notations], [aSig policyURLs]];
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

- (IBAction) verify:(id)sender
{
    NSOpenPanel	*openPanel = [NSOpenPanel openPanel];
	
    [openPanel setAllowsMultipleSelection:NO];
    [openPanel setCanChooseDirectories:NO];
    [openPanel setCanChooseFiles:YES];
    [openPanel setAllowsMultipleSelection:NO];
    [openPanel setTreatsFilePackagesAsDirectories:YES];
	
    if([openPanel runModalForTypes:nil] == NSOKButton){
        [self authenticateFile:[openPanel filename] againstSignatureFile:nil];
    }
}

- (IBAction) verifyDetachedSignature:(id)sender
{
    NSOpenPanel	*openPanel = [NSOpenPanel openPanel];
	
    [openPanel setAllowsMultipleSelection:NO];
    [openPanel setCanChooseDirectories:NO];
    [openPanel setCanChooseFiles:YES];
    [openPanel setAllowsMultipleSelection:NO];
    [openPanel setTreatsFilePackagesAsDirectories:YES];
	
    if([openPanel runModalForTypes:nil] == NSOKButton){
        NSString	*inputFilename = [[openPanel filename] copy];
		
        [openPanel setPrompt:@"Signature:"];
		
        if([openPanel runModalForTypes:nil] == NSOKButton){
            [self authenticateFile:inputFilename againstSignatureFile:[openPanel filename]];
        }
        [inputFilename release];
    }
}

- (void) keyringChanged:(NSNotification *)notif
{
    NSLog(@"keyringChanged: %@", [notif userInfo]);
    [keyTableView noteNumberOfRowsChanged];
    [keyTableView reloadData];
}

+ (GPGContext *) keySignatureBrowserContext
{
    static GPGContext   *keySignatureBrowserContext = nil;
    
    if(keySignatureBrowserContext == nil){
        keySignatureBrowserContext = [[GPGContext alloc] init];
        [keySignatureBrowserContext setKeyListMode:GPGKeyListModeSignatures | GPGKeyListModeLocal | GPGKeyListModeSignatureNotations];
    }
    
    return keySignatureBrowserContext;
}

+ (NSMutableDictionary *) signerPerUserIDCache
{
    static NSMutableDictionary  *signerPerUserIDCache = nil;
    
    if(signerPerUserIDCache == nil){
        signerPerUserIDCache = [[NSMutableDictionary alloc] init];
    }
    
    return signerPerUserIDCache;
}

- (void) reloadSelectedKeyUserIDsWithSignaturesFromKey:(GPGKey *)key
{
    if(key != nil){
        GPGContext  *aContext = [[self class] keySignatureBrowserContext];
        
        key = [aContext keyFromFingerprint:[key fingerprint] secretKey:NO];
        [self willChangeValueForKey:@"selectedKeyUserIDsWithSignatures"];
        [selectedKeyUserIDsWithSignatures autorelease];
        if(key != nil)
            selectedKeyUserIDsWithSignatures = [[key userIDs] retain];
        else
            selectedKeyUserIDsWithSignatures = nil;
        [[[self class] signerPerUserIDCache] removeAllObjects];
        [self didChangeValueForKey:@"selectedKeyUserIDsWithSignatures"];
    }
}

- (NSArray *) selectedKeyUserIDsWithSignatures
{
    return selectedKeyUserIDsWithSignatures;
}

- (IBAction) testKeyFromFingerprintLeaks:(id)sender
{
    volatile int                i = 0;
    volatile NSAutoreleasePool  *localAP = nil;
    
    NS_DURING
	for(i = 0; i < 100; i++){
		localAP = [[NSAutoreleasePool alloc] init];
		
		(void)[[[self class] keySignatureBrowserContext] keyFromFingerprint:@"0x992020D4" secretKey:NO];
		[localAP release];
	}
    NS_HANDLER
	[localAP release];
	NSLog(@"Failed after %d attempts: %@", i, localException);
    NS_ENDHANDLER
}

@end