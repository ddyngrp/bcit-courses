/*
	PKController.m
	GPG Keychain Access

	Created by craigc@users.sourceforge.net on 2001-09-25.

	$Id: PKController.m 1699 2005-06-20 12:31:03Z rhwood $

	Copyright (C) 2001-2005 Mac GPG Project.

	This code is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2 of the License, or any later version.

	This code is distributed in the hope that it will be useful, but WITHOUT ANY
	WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
	FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
	details.

	For a copy of the GNU General Public License, visit <http://www.gnu.org/> or
	write to the Free Software Foundation, Inc., 59 Temple Place--Suite 330,
	Boston, MA 02111-1307, USA.

	More info at <http://macgpg.sourceforge.net/>
 */

#import "PKController.h"

#import "PKOutlineDataSource.h"
#import "Preferences.h"
#import "RecvKeyController.h"
#import "SearchKeyController.h"
#import "PKInspectorController.h"

#import <MacGPGME/MacGPGME.h>

@implementation PKController

/*====================================
 application delegate
====================================*/

/*
- (void)applicationWillTerminate:(NSNotification *)notification
{
    [Preferences saveDefaults];
}
*/

/*
 * If the application is launched by double clicking on a file, we attempt to import any keys within the file.
 */ 
- (BOOL)application:(NSApplication *)sender openFile:(NSString *)filename
{
    if ([self importKeyFromFile: filename]) {
        NSRunInformationalAlertPanel(NSLocalizedStringFromTable(PKImportSheetTitle,
																@"Localizable",
																PKImportSheetTitle),
                                     NSLocalizedStringFromTable(PKImportSuccessString,
																@"Localizable",
																PKImportSuccessString),
									 nil,
									 nil,
									 nil);
	}
    return YES;
}

/*
 * Open the Keychains window if it is not already open.
 */
- (BOOL)applicationShouldHandleReopen:(NSApplication *)theApplication hasVisibleWindows:(BOOL)flag
{
	if (!flag) {
		[self showKeychains:nil];
	}
	return YES;
}

/*
 * Test that the user has a secret key available. If the user has no secret keys, inform the user of that fact.
 */
- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
	if (![[[[[[GPGContext alloc] init] autorelease] keyEnumeratorForSearchPattern:nil secretKeysOnly:YES] allObjects] count]) {
		NSString *path;
		path = [[[NSProcessInfo processInfo] environment] objectForKey:@"GNUPGHOME"];
		if (!path || [path isEqualToString:@""]) {
			[path release];
			path = [[[NSString alloc] initWithString:@"~/.gnupg"] stringByStandardizingPath];
		}
		if (![[NSFileManager defaultManager] fileExistsAtPath:[path stringByAppendingPathComponent:@"gpg.conf"]]) {
			[self runCommandWithString:@"--list-keys"];
		}
		switch (NSRunAlertPanel(
								NSLocalizedStringFromTable(@"You do not have a private or secret key.",
														   @"Localizable",
														   @"awakeFromNib: error: no secret key: title"),
								NSLocalizedStringFromTable(@"You may choose to generate a new key, import an existing key from elsewhere, or quit this application to fix your GnuPG installation.\n",
														   @"Localizable",
														   @"awakeFromNib: error: no secret key: statement"),
								NSLocalizedStringFromTable(@"Generate",
														   @"Localizable",
														   @"awakeFromNib: error: no secret key: generate"),
								NSLocalizedStringFromTable(@"Import",
														   @"Localizable",
														   @"awakeFromNib: error: no secret key: import"),
								NSLocalizedStringFromTable(@"Quit",
														   @"Localizable",
														   @"awakeFromNib: error: no secret key: quit")
								)) {
			case NSAlertDefaultReturn:
				[self keyGenerate:nil];
				break;
			case NSAlertAlternateReturn:
				[self fileImport:nil];
				break;
			default:
				[NSApp terminate:nil];
		}
	}
}

- (void)awakeFromNib
{
#if VERBOSE_LOGGING == 0
	if (_verboseLogging)
#endif
		NSLog([self niceGPGMEVersion]);
	[pkWindow setExcludedFromWindowsMenu:YES]; // hide duplicate items in Windows menu
	[keychainsWindowMenu setState:NSOnState];
	
    [pkOutline setDoubleAction:@selector(doubleClick:)];
    [pkOutline setTarget:self];

    _refreshing = YES;
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didBeginRefresh:) name:@"GKA_PKBeginRefresh" object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didEndRefresh:) name:@"GKA_PKEndRefresh" object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(listRefresh:) name:@"GPGPipedProcessDidEnd" object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(updateKeyListStatus:) name:@"GKA_PKCountOfKeysInViewChanged" object:nil];
	[[NSDistributedNotificationCenter defaultCenter] addObserver:self selector:@selector(listRefresh:) name:@"GPGTerminalOperationDidEnd" object:nil];
	
	// attach a menu to the pkOutline header row
	[[pkOutline headerView] setMenu:pkOutlineHeaderMenu];
	[[pkOutline cornerView] setMenu:pkOutlineHeaderMenu];
    [pkOutlineDS setupTableColumns];
    [self listRefresh:nil];
}

- (BOOL)validateMenuItem:(NSMenuItem *)menuItem
{
    if ([pkOutline numberOfSelectedRows] == 0)	{
        if (menuItem == deleteKeyMenu || menuItem == signKeyMenu || menuItem == editKeyMenu ||
        menuItem == lsignKeyMenu || menuItem == sendKeyMenu || menuItem == syncKeyMenu ||
        menuItem == exportMenu)
            return NO;
    }
    if ([pkOutline numberOfSelectedRows] != 1 && menuItem == showInfoMenu) {
        return NO;
	}
    if ((menuItem  == refreshMenu) && (_refreshing == YES)) {
        return NO;
	}
    return YES;
}

/*
 * Since PKController is the target for these toolbar items,
 * PKController must validate these items.
 */
- (BOOL)validateToolbarItem:(NSToolbarItem *)theItem
{
	if (([pkOutline numberOfSelectedRows] == 0) &&
		([theItem action] == @selector(keyDelete:) ||
		[theItem action] == @selector(fileExport:) ||
		[theItem action] == @selector(keySign:) ||
		[theItem action] == @selector(keyEdit:))) {
		return NO;
	}
	if ([pkOutline numberOfSelectedRows] != 1 &&
		[theItem action] == @selector(showWindow)) {
		return NO;
	}
	return YES;
}

- (void)didBeginRefresh:(NSNotification *)notification
{
    _refreshing = YES;
	[pkProg startAnimation:nil];
    [pkOutline deselectAll:self];
    //some UI elements are changed in the thread
    //to make sure that they get changed in time
}

- (void)didEndRefresh:(NSNotification *)notification
{
    _refreshing = NO;
	[pkProg stopAnimation:nil];
}

- (void)updateKeyListStatus:(NSNotification *)notification
{
	[keyListStatus setStringValue:
		[NSString stringWithFormat:
			NSLocalizedStringFromTable(
									   @"%i of %i keys listed",
									   @"Localizable",
									   @"keyListStatus"),
			[pkOutlineDS countOfKeysInView],
			[pkOutlineDS countOfKeysInKeychain]]];
}

// Deallocate the toolbarItems
- (void) dealloc
{
    [super dealloc];
}

- (BOOL) verboseLogging
{
	return _verboseLogging;
}

- (void) setVerboseLogging:(BOOL)state
{
	_verboseLogging = state;
}

@end

@implementation PKController (IBActions)

- (IBAction)fileExport:(id)sender
{
    /*
    //you can't export secret keys at the moment, so not yet needed
    if ([self secretKeysAreVisible])
        NSRunInformationalAlertPanel([PKLocalizableStrings warning],
                                     NSLocalizedStringFromTable(PKWarningSecretKeyExportString,PKWarningSecretKeyExportString),
                                     nil, nil, nil);
     */
    NS_DURING
        GPGContext *gpg_context = [[[GPGContext alloc] init] autorelease];
        
        NSSavePanel	*sp;
        GPGData		*exported_data;
        NSMutableString *filename;
        
        sp = [NSSavePanel savePanel];
        
        [sp setTreatsFilePackagesAsDirectories:YES];
        [sp setAccessoryView: pkExportKeyOptionsView];

        filename = [NSMutableString string];
        if ([[[self selectedKeys] allObjects] count] == 1)
            [filename appendString: [[self selectedKeysByID] nextObject]];
        else
            [filename appendString: @"untitled"];
        [filename appendString: @".gpgkey"];

        if([sp runModalForDirectory: nil file: filename] == NSOKButton){
            [gpg_context setUsesArmor: [pkArmoredCkBox state] ? YES : NO];
            exported_data = [gpg_context exportedKeys:[[self selectedKeys] allObjects]];

            [[exported_data data] writeToFile:[sp filename] atomically:NO];
        }
    NS_HANDLER
        [self handleException: localException];
    NS_ENDHANDLER
}

- (IBAction)fileImport:(id)sender
{
    NSOpenPanel *op;
    int answer;
    BOOL yes_all;
    BOOL allow_secret;

    op = [NSOpenPanel openPanel];
    yes_all = NO;

    //[op setAllowsMultipleSelection:YES];
    [op setCanChooseDirectories:NO];
    [op setCanChooseFiles:YES];
    [op setAllowsMultipleSelection:YES];
    [op setTreatsFilePackagesAsDirectories:YES];
    [op setAccessoryView: pkImportKeyOptionsView];
    
    answer = [op runModal];
    allow_secret = [pkAllowSecretKeyImportCkBox state] ? YES : NO;

    if (answer == NSOKButton && !allow_secret)	{
        int i;
        yes_all = YES;
        for (i = 0; i < [[op filenames] count]; i++)	{
            if (![self importKeyFromFile: [[op filenames] objectAtIndex: i]])
                yes_all = NO;
        }
        if (yes_all)	{
            NSRunInformationalAlertPanel(NSLocalizedStringFromTable(PKImportSheetTitle, @"Localizable", PKImportSheetTitle),
                                         NSLocalizedStringFromTable(PKImportSuccessString, @"Localizable", PKImportSuccessString), nil, nil, nil);
            [self listRefresh: self];
        }
    }
    else if (answer == NSOKButton && allow_secret)	{
        NSMutableString *script = [NSMutableString stringWithString: @"gpg --allow-secret-key-import --import \\\""];
        [script appendString: [[op filenames] componentsJoinedByString: @"\\\" \\\""]];
        [script appendString: @"\\\""];
        [self runScriptInTerminal: script];
    }
        //else nothing happens
}

- (BOOL)importKeyFromFile: (NSString *)filename
{
#warning you can pass in invalid data and no exception is raised; fixed in latest gpg builds
    BOOL return_value;
    NS_DURING
        GPGData *new_key;
        GPGContext *gpg_context = [[GPGContext alloc] init];

        new_key = [[GPGData alloc] initWithContentsOfFile: filename];
        [gpg_context importKeyData: new_key];
        [new_key release];
        [gpg_context release];
        return_value = YES;
    NS_HANDLER
        [self handleException: localException];
        return_value = NO;
    NS_ENDHANDLER
    return return_value;
}    

- (IBAction)keyDelete:(id)sender
{
    NSEnumerator *selectedKeys;
    GPGKey *currentKey;
    GPGContext *context = [[[GPGContext alloc] init] autorelease];
	BOOL deletionConfirmed;

    selectedKeys = [self selectedKeys];
    while ((currentKey = [selectedKeys nextObject])) {
        if ([[currentKey secretKey] isSecret]) {
            deletionConfirmed = !NSRunAlertPanel(
												 [PKLocalizableStrings warning],
												 NSLocalizedStringFromTable(
																			PKWarningSecretKeyDeleteString,
																			@"Localizable",
																			PKWarningSecretKeyDeleteString),
												 [PKLocalizableStrings no],
												 [PKLocalizableStrings yes],
												 nil,
												 [currentKey userID],
												 [currentKey shortKeyID]);
		} else {
			deletionConfirmed = NSRunAlertPanel(
												[PKLocalizableStrings warning],
												NSLocalizedStringFromTable(
																		   PKWarningKeyDeleteString,
																		   @"Localizable",
																		   PKWarningKeyDeleteString),
												[PKLocalizableStrings yes],
												[PKLocalizableStrings no],
												nil,
												[currentKey userID],
												[currentKey shortKeyID]);
			
		}
        if (deletionConfirmed) {
            NS_DURING
                [context deleteKey:currentKey evenIfSecretKey:YES];
            NS_HANDLER
                [self handleException:localException];
            NS_ENDHANDLER
            [self listRefresh:self];
        }
    }
}

- (IBAction)keyEdit:(id)sender
{
    NSEnumerator *sel_keys;
    NSString *key_id;

    sel_keys = [self selectedKeysByID];
    while ((key_id = [sel_keys nextObject]))	{
        NSMutableString *script;

        script = [NSMutableString stringWithString: @"gpg --edit-key "];
        [script appendString: key_id];

        [self runScriptInTerminal: script];
    }
}

- (IBAction)keyInformation:(id)sender
{
	GKAKeyInformation *keyInformation;
	GPGContext *context = [[GPGContext alloc] init];
	keyInformation = [[GKAKeyInformation alloc] init];
	[keyInformation setKey:[[[self selectedKeys] allObjects] objectAtIndex:0]];
	//keyInformation = [[[GKAKeyInformation alloc] initWithKey:[[[context keyEnumeratorForSearchPattern:[pkOutline itemAtRow:[pkOutline selectedRow]] secretKeysOnly:NO] allObjects] objectAtIndex: 0]] retain];
	[context release];
	[keyInformation showWindow:self];
}

- (IBAction)keyGenerate:(id)sender
{
//	GenerateKeyController *keyGenerator;
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(listRefresh:) name:@"GPGGenerateKeyDidEnd" object:nil];
//	keyGenerator = [GenerateKeyController sharedInstance];
//	keyGenerator = [[[GenerateKeyController alloc] init] retain];
//	[keyGenerator showWindow:nil];
//	[keyGenerator release];
	[[GenerateKeyController sharedInstance] showWindow:nil];
}

- (IBAction)keyReceive:(id)sender
{
    if (recvKeyController == nil)
    {
        recvKeyController = [[RecvKeyController alloc] initWithWindowNibName:@"RecvKeyPanel"];
        if (recvKeyController == nil)
        {
            NSLog(@"Failed to load RecvKeyPanel.nib");
            NSBeep();
            return;
        }
    }
    [NSApp runModalForWindow: [recvKeyController window]];
    [recvKeyController release];
    recvKeyController = nil;
}

- (IBAction)keySearch:(id)sender
{
	[[SearchKeyController sharedInstance] searchForKeyWithSearchString:[sender stringValue]];
}

- (IBAction)keySend:(id)sender
{
    NSEnumerator *sel_keys;
    NSString *key_id;

    sel_keys = [self selectedKeysByID];
    while ((key_id = [sel_keys nextObject]))	{
        NSMutableString *script;

        script = [NSMutableString stringWithString: @"gpg --send-key "];
        [script appendString: key_id];

        [self runScriptInTerminal: script];
    }    
}

- (IBAction)keySign:(id)sender
{
    NSEnumerator *sel_keys;
    NSString *key_id;

    sel_keys = [self selectedKeysByID];
    while ((key_id = [sel_keys nextObject]))	{
        NSMutableString *script;

        script = [NSMutableString stringWithString: @"gpg --sign-key "];
        [script appendString: key_id];

        [self runScriptInTerminal: script];
    }    
}

- (IBAction)keySignLocal:(id)sender
{
    NSEnumerator *sel_keys;
    NSString *key_id;

    sel_keys = [self selectedKeysByID];
    while ((key_id = [sel_keys nextObject]))	{
        NSMutableString *script;

        script = [NSMutableString stringWithString: @"gpg --lsign-key "];
        [script appendString: key_id];

        [self runScriptInTerminal: script];
    }    
}

/*
 * Update key from server. Does not sync anything.
 */
- (IBAction)keySync:(id)sender
{
    NSEnumerator *sel_keys;
	NSString *key_id;

    sel_keys = [self selectedKeysByID];
    while ((key_id = [sel_keys nextObject]))	{
		[self runCommandWithArray: [NSArray arrayWithObjects:@"--recv-key", key_id, nil]];
    }    
}

/*
 Archive the entire gpg keychain to a file for portability or backups
 */
- (IBAction)keyBackup:(id)sender
{
	
}

- (IBAction)updateTrustDB:(id)sender
{
    NSString *script;

    script = [NSString stringWithString: @"gpg --update-trustdb"];
    [self runScriptInTerminal: script];    
}

- (IBAction)rebuildKeyDBCaches:(id)sender
{
    NSString *script;

    script = [NSString stringWithString: @"gpg --rebuild-keydb-caches"];
    [self runScriptInTerminal: script];    
}

- (IBAction)listRefresh:(id)sender
{
	// this is a bit brute force, but it brings GPGKA to the front with all
	// its windows after a terminal operation has completed.
	[NSApp activateIgnoringOtherApps:YES];
	[NSApp arrangeInFront:sender];
    [[pkOutline dataSource] refresh:sender];
}

- (IBAction)listFilter:(id)sender
{
    [[pkOutline dataSource] filter:sender];
}

- (IBAction) toggleColumnDisplay:(id)sender
{
	if ([sender tag]) {
		NSTableColumn *aColumn = [allTableColumns objectAtIndex:[sender tag]];
		if([sender state] != NSOnState){
			NSArray			*defaultColumnWidths = [[NSUserDefaults standardUserDefaults] arrayForKey:@"TableColumnWidths"];
			if(defaultColumnWidths != nil && [defaultColumnWidths lastObject] != nil)
				[aColumn setWidth:[[defaultColumnWidths objectAtIndex:[sender tag]] floatValue]];
			[pkOutline addTableColumn:aColumn];
		}
		else{
			[pkOutline removeTableColumn:aColumn];
		}
		[sender setState:![sender state]];
	}
}

- (void) doubleClick:(id)sender
{
    [inspectorController showWindow:sender];
}

/*
 * Shows the about box with information about underlying frameworks and engines
 *
 * TODO: localize all string literals.
 * TODO: make the credits string font match the font used in the about box.
 */
- (IBAction)showAboutBox:(id)sender
{
	NSMutableDictionary *options;
	NSMutableAttributedString *credits;
	NSMutableString *version;
	NSEnumerator *engines;
	GPGEngine *engine;
	
	engines = [[GPGEngine availableEngines] objectEnumerator];
	version = [[NSMutableString alloc] init];
	while (engine = [engines nextObject]) {
		[version appendString:GPGLocalizedProtocolDescription([engine engineProtocol])];
		[version appendString:@": "];
		[version appendString:[engine version]];
		[version appendString:@" ("];
		[version appendString:[engine executablePath]];
		[version appendString:@")\n"];
	}
	[version deleteCharactersInRange:NSMakeRange([version length] - 1, 1)];
	credits = [[NSMutableAttributedString alloc] initWithString:[self niceGPGMEVersion]];

	[credits setAlignment:NSCenterTextAlignment range:NSMakeRange(0, [credits length])];
	[credits addAttribute:@"NSFontAttributeName" value:[NSFont labelFontOfSize:[NSFont labelFontSize]] range:NSMakeRange(0, [credits length])];
	options = [[NSMutableDictionary alloc] init];
	[options setObject:credits forKey:@"Credits"];
	[NSApp orderFrontStandardAboutPanelWithOptions:options];
}

/*!
 * @abstract	Display the GnuPG preferences pane
 *
 * @discussion	Displays the GnuPG.prefpane bundle using System Preferences.
 *				If the bundle is not installed in the default location,
 *				nothing happens.
 */
- (IBAction)showPreferences:(id)sender
{
#if USE_SYSTEM_PREFERENCES == 1
	NSEnumerator *libraries;
	NSString *prefPane;
	BOOL prefPaneInstalled = NO;
	libraries = [NSSearchPathForDirectoriesInDomains(
												  NSLibraryDirectory,
												  NSAllDomainsMask,
												  YES)
		objectEnumerator];
	while (prefPane = [libraries nextObject]) {
		prefPane = [prefPane stringByAppendingPathComponent:@"/PreferencePanes/GnuPG.prefPane"];
		NSLog(prefPane);
		if ([[NSWorkspace sharedWorkspace] isFilePackageAtPath:prefPane]) {
			[[NSWorkspace sharedWorkspace] openFile:prefPane];
			prefPaneInstalled = YES;
			break;
		}
	}
	if (!prefPaneInstalled) {
		if (NSAlertDefaultReturn == NSRunAlertPanel(NSLocalizedStringFromTable(PKSystemPreferencesError,
																			   @"Localizable",
																			   PKSystemPreferencesError),
													NSLocalizedStringFromTable(PKSystemPreferencesSolution,
																			   @"Localizable",
																			   PKSystemPreferencesSolution),
													[PKLocalizableStrings yes],
													[PKLocalizableStrings no],
													nil, nil)) {
			[[NSWorkspace sharedWorkspace]
				openFile:[[[NSBundle mainBundle]
					resourcePath]
					stringByAppendingPathComponent:@"/GPGPreferences-1.2.pkg"]];
		}
	}
#else
	preferences = [[PKPreferencesController alloc] init];
	[preferences showPreferences:sender];
	[preferences release];
#endif
}

/*!
 * @abstract	Display the GNU Privacy Handbook in response to a menu selection.
 *
 * @discussion	Currently is not localized. Needs to be.
 */
- (void) showGnuPrivacyHandbook:(id)sender
{
	if (![[NSWorkspace sharedWorkspace] openFile:
		NSLocalizedStringFromTable(
							   @"/Library/Documentation/GnuPG/English/The GNU Privacy Handbook.pdf",
							   @"Localizable",
							   @"showGnuPrivacyHandbook: localized Gnu Privacy Handbook location")]) {
		NSRunAlertPanel(
				  NSLocalizedStringFromTable(PKErrorSheetTitle,
								 @"Localizable",
								 PKErrorSheetTitle),
				  NSLocalizedStringFromTable(PKErrorGPHandbook,
								 @"Localizable",
								 PKErrorGPHandbook),
				  nil, nil, nil);
	}
}

/*!
 * @abstract	Display the GPL in a browser window.
 *
 * @discussion	The GPL statement is localized and stored in the bundle as an HTML document.
 */
- (void) showGPL:(id)sender
{
	NSString *GPL;
	NSBundle *thisBundle = [NSBundle bundleForClass:[self class]];
	if (GPL = [thisBundle pathForResource:@"GPL" ofType:@"html"]) {
		[[NSWorkspace sharedWorkspace] openFile:GPL];
	}
}

/*!
 * @abstract	Display developer credits and other acknowledgments
 *
 * @discussion	Acknowledgments are localized and stored inside the bundle.
 */
- (void) showAcknowledgments:(id)sender
{
	NSString *acknowledgments;
	NSBundle *thisBundle = [NSBundle bundleForClass:[self class]];
	if (acknowledgments = [thisBundle pathForResource:@"Credits" ofType:@"html"]) {
		[[NSWorkspace sharedWorkspace] openFile:acknowledgments];
	}
}

/*
 *	Display the keychains window if it is not already displayed
 */
- (void) showKeychains:(id)sender
{
	[pkWindow makeKeyAndOrderFront:sender];
	[keychainsWindowMenu setState:NSOnState];
}

/*
 * Close whichever window has the focus
 */
- (void) closeFrontAndKeyWindow:(id)sender
{
	if ([[NSApp keyWindow] isEqualTo:pkWindow]) {
		[self closeKeychains:sender];
	} else {
		[[NSApp keyWindow] performClose:sender];
	}
}

/*
 *	Closes the keychains window
 */
- (void) closeKeychains:(id)sender
{
	[pkWindow close];
	[keychainsWindowMenu setState:NSOffState];
}

@end

@implementation PKController (Utility)

/*
 * Pass pipeToGPG arguments as a string instead of an array
 */
- (void) runCommandWithString:(NSString *)command {
	[self runCommandWithArray:[command componentsSeparatedByString:@" "]];
}

/*
 * Use this to pipe commands to GPG if GPGME can't do what we want
 *
 * Current limitations:
 *		All feedback from GPG gets dumped to the console
 *		No feedback is provided to calling command to alert user to unexpected results
 */
- (void) runCommandWithArray:(NSArray *)command {
	NSTask *gnupg;
	NSPipe *pipeIn;
	NSFileHandle *dataIn;
	NSAutoreleasePool *pool;
	
	pool = [[NSAutoreleasePool alloc ] init];
	[[NSNotificationCenter defaultCenter] postNotificationName:@"GPGPipedProcessDidBegin" object:self];
	NS_DURING
		gnupg = [[NSTask alloc] init];
		pipeIn = [NSPipe pipe];
		dataIn = [pipeIn fileHandleForWriting];
		//			[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(generateKeyProgress:) name:@"GPGProgressNotification" object:nil];
		[gnupg setStandardInput:pipeIn];
		[gnupg setLaunchPath:@"/usr/local/bin/gpg"];
		[gnupg setArguments:command];
		[gnupg launch];
		//			[dataIn writeData:[keyData dataUsingEncoding:[keyData fastestEncoding]]];
		[dataIn closeFile];
		[pkProg startAnimation:nil];
		while ([gnupg isRunning]) {
			[[NSNotificationCenter defaultCenter]
    postNotificationName:@"GPGProgressNotification" object:self];
		}
		[gnupg waitUntilExit];
	NS_HANDLER
	NS_ENDHANDLER
		
	[pkProg stopAnimation:nil];
	[[NSNotificationCenter defaultCenter] postNotificationName:@"GPGPipedProcessDidEnd" object:self];
	[pool release];
}

- (void) handleException:(NSException *) exception {
    switch (GPGErrorCodeFromError((int)[[exception userInfo] objectForKey:GPGErrorKey])) {
        case GPGErrorCancelled:
            break;
        default:
            NSRunAlertPanel(NSLocalizedStringFromTable(PKErrorSheetTitle, @"Localizable", PKErrorSheetTitle),
                            [exception reason], nil, nil, nil);
    }
}

- (NSEnumerator *) selectedKeysByID
{
    if([pkOutline numberOfSelectedRows] <= 0)
        return nil;
    else{
        NSNumber *row;
        NSEnumerator *selected_rows;
        NSMutableArray *keys;
        
        selected_rows = [pkOutline selectedRowEnumerator];
        keys = [NSMutableArray array];
        
        while ((row = [selected_rows nextObject]))	{
            int row_int = [row intValue];
            if ([pkOutline levelForRow: row_int] == 0)	{
                [keys addObject: [[pkOutline itemAtRow: row_int] objectForKey: @"fpr"]];
            }
        }
        return [keys objectEnumerator];
    }
}

- (NSEnumerator *) selectedKeys
{
    if([pkOutline numberOfSelectedRows] <= 0)
        return nil;
    else{
        GPGContext *context = [[GPGContext alloc] init];
        NSNumber *row;
        NSString *key_id;
        NSEnumerator *selected_rows, *keys_enum;
        NSMutableArray *keys, *sel_keys;

        selected_rows = [pkOutline selectedRowEnumerator];
        keys = [NSMutableArray array];
        sel_keys = [NSMutableArray array];

        while ((row = [selected_rows nextObject]))	{
            int row_int = [row intValue];
            if ([pkOutline levelForRow: row_int] == 0)	{
                [keys addObject: [[pkOutline itemAtRow: row_int] objectForKey: @"fpr"]];
            }
        }

        keys_enum = [keys objectEnumerator];
        
        while ((key_id = [keys_enum nextObject]))	{
            [sel_keys addObjectsFromArray: [[context keyEnumeratorForSearchPattern: key_id secretKeysOnly:
                NO] allObjects]];
        }

        [context release];
        
        return [sel_keys objectEnumerator];
    }
}    

- (void)runScriptInTerminal:(NSString *)script
{
	[self runScriptInTerminal:script withNotification:@"GPGTerminalOperationDidEnd"];
}

- (void)runScriptInTerminal:(NSString *)script withNotification:(NSString *)notification
{
	[self runScriptInTerminal:script withNotification:notification terminalWindowShouldClose:NO];
}

- (void)runScriptInTerminal:(NSString *)script withNotification:(NSString *)notification terminalWindowShouldClose:(BOOL)terminalWindowShouldClose
{
    NSTask *edit_task, *activate_task;
    NSMutableArray *args;
    NSMutableString *as_script;

    //task to activate Terminal
    args = [NSMutableArray array];
    [args addObject: @"-e"];
    [args addObject: @"tell application \"Terminal.app\" to activate"];

    activate_task = [[NSTask alloc] init];
    [activate_task setLaunchPath: @"/usr/bin/osascript"];
    [activate_task setArguments: args];

    [activate_task launch];
    [activate_task release];

    //run script
    as_script = [NSMutableString stringWithString: @"tell application \"Terminal.app\" to do script with command \""];
    [as_script appendString: script];
	[as_script appendString: @" ; "];
	[as_script appendString: [[[[NSBundle mainBundle] pathForResource:@"notificationtool" ofType:nil] componentsSeparatedByString:@" "] componentsJoinedByString:@"\\\\ "]];
	[as_script appendString: @" "];
	[as_script appendString: notification];
	if (terminalWindowShouldClose) {
		[as_script appendString: @" ; sleep 30 ; exit"];
	}
    [as_script appendString: @"\""];
    
    [args removeLastObject];
    [args addObject: as_script];
    
    edit_task = [[NSTask alloc] init];
    [edit_task setLaunchPath: @"/usr/bin/osascript"];
    [edit_task setArguments: args];

    [edit_task launch];
    [edit_task waitUntilExit];  //lets the user know that their waiting for something
    [edit_task release];
}

- (NSString *) niceGPGMEVersion
{
	NSMutableString *version;
	NSEnumerator *engines;
	GPGEngine *engine;
	
	engines = [[GPGEngine availableEngines] objectEnumerator];
	version = [[NSMutableString alloc] init];
	while (engine = [engines nextObject]) {
		[version appendString:GPGLocalizedProtocolDescription([engine engineProtocol])];
		[version appendString:@": "];
		[version appendString:[engine version]];
		[version appendString:@" ("];
		[version appendString:[engine executablePath]];
		[version appendString:@")\n"];
	}
	[version deleteCharactersInRange:NSMakeRange([version length] - 1, 1)];
	return [NSString stringWithFormat:
			NSLocalizedStringFromTable(@"Component versions\nGPGME: %@\n%@",
									   @"Localizable",
									   @"showAboutBox: component version data"),
			[GPGEngine checkFrameworkVersion:nil],
			version];
	
}

@end