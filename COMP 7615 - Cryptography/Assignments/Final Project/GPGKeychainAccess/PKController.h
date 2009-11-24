//
//  PKController.h
//  GPG Keychain Access
//
//  Created by craigc@users.sourceforge.net on 2001-09-25.
//
//
//  Copyright (C) 2001 Mac GPG Project.
//  
//  This code is free software; you can redistribute it and/or modify it under
//  the terms of the GNU General Public License as published by the Free
//  Software Foundation; either version 2 of the License, or any later version.
//  
//  This code is distributed in the hope that it will be useful, but WITHOUT ANY
//  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
//  FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
//  details.
//  
//  For a copy of the GNU General Public License, visit <http://www.gnu.org/> or
//  write to the Free Software Foundation, Inc., 59 Temple Place--Suite 330,
//  Boston, MA 02111-1307, USA.
//  
//  More info at <http://macgpg.sourceforge.net/> or <macgpg@rbisland.cx>
//

#import <Cocoa/Cocoa.h>
#import <MacGPGME/MacGPGME.h>
#import "GPGKeys_PREFIX.h"
#import "PKLocalisableStrings.h"
#import "TBLocalizableStrings.h"

#import "GenerateKeyController.h"
#import "KeyInformation.h"
#import "TBController.h"

@class GenerateKeyController;
@class PKOutlineDataSource;
@class PKPreferencesController;
@class RecvKeyController;
@class SearchKeyController;
@class PKInspectorController;
@class TBLocalizableStrings;
@class TBController;

@interface PKController : NSObject
{
    IBOutlet NSWindow *pkWindow;
    IBOutlet NSOutlineView *pkOutline;
    IBOutlet PKOutlineDataSource *pkOutlineDS;
    IBOutlet NSProgressIndicator *pkProg;
    IBOutlet NSButton *pkArmoredCkBox;
    IBOutlet NSView *pkExportKeyOptionsView;
    IBOutlet NSButton *pkAllowSecretKeyImportCkBox;
    IBOutlet NSView *pkImportKeyOptionsView;
	IBOutlet NSTextField *keyListStatus;
    
    PKPreferencesController *preferences;
    RecvKeyController *recvKeyController;
    SearchKeyController *searchKeyController;
    IBOutlet PKInspectorController *inspectorController;

    IBOutlet NSMenuItem *refreshMenu,
		*deleteKeyMenu,
		*signKeyMenu,
		*editKeyMenu,
        *lsignKeyMenu,
		*sendKeyMenu,
		*syncKeyMenu,
		*exportMenu,
		*showInfoMenu,
		*keychainsWindowMenu;
    
    BOOL _refreshing;

    NSTableColumn	*sortingTableColumn;
	IBOutlet NSMenu	*pkOutlineHeaderMenu;
    NSMutableArray	*allTableColumns;
    NSMutableArray	*selectedItems;
    BOOL			isUpdatingSelection;
	
	BOOL	_verboseLogging;
}

//- (void)applicationWillTerminate:(NSNotification *)notification;
- (BOOL)applicationShouldHandleReopen:(NSApplication *)theApplication hasVisibleWindows:(BOOL)flag;
- (void)awakeFromNib;
- (BOOL)validateMenuItem:(NSMenuItem *)menuItem;
- (BOOL)validateToolbarItem:(NSToolbarItem *)theItem;
- (void)updateKeyListStatus:(NSNotification *)notification;
- (BOOL)verboseLogging;
- (void)setVerboseLogging:(BOOL)state;

@end

@interface PKController (IBActions)

- (IBAction)fileExport:(id)sender;
- (IBAction)fileImport:(id)sender;
- (BOOL)importKeyFromFile:(NSString *)filename;

- (IBAction)keyDelete:(id)sender;
- (IBAction)keyEdit:(id)sender;
- (IBAction)keyGenerate:(id)sender;
- (IBAction)keyReceive:(id)sender;
- (IBAction)keySearch:(id)sender;
- (IBAction)keySend:(id)sender;
- (IBAction)keySign:(id)sender;
- (IBAction)keySignLocal:(id)sender;
- (IBAction)keySync:(id)sender;
- (IBAction)keyInformation:(id)sender;
- (IBAction)keyBackup:(id)sender;

- (IBAction)updateTrustDB:(id)sender;
- (IBAction)rebuildKeyDBCaches:(id)sender;

- (IBAction)listRefresh:(id)sender;
- (IBAction)listFilter:(id)sender;

- (IBAction)toggleColumnDisplay:(id)sender;

// Application menu
// Use standard About box
- (IBAction)showAboutBox:(id)sender;
- (IBAction)showPreferences:(id)sender;

// File menu
- (IBAction)closeKeychains:(id)sender;
- (IBAction)closeFrontAndKeyWindow:(id)sender;

// Window menu
- (IBAction)showKeychains:(id)sender;

// Help menu
- (IBAction)showGnuPrivacyHandbook:(id)sender;
- (IBAction)showGPL:(id)sender;
- (IBAction)showAcknowledgments:(id)sender;

@end

@interface PKController (Utility)

- (void)handleException:(NSException *)exception;
- (NSEnumerator *)selectedKeysByID;
- (NSEnumerator *)selectedKeys;
- (void)runCommandWithString:(NSString *)command;
- (void)runCommandWithArray:(NSArray *)command;
- (void)runScriptInTerminal:(NSString *)script;
- (void)runScriptInTerminal:(NSString *)script withNotification:(NSString *)notification;
- (void)runScriptInTerminal:(NSString *)script withNotification:(NSString *)notification terminalWindowShouldClose:(BOOL)terminalWindowShouldClose;

- (NSString *)niceGPGMEVersion;

@end