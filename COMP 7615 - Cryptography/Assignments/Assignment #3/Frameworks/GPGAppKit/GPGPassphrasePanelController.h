//
//  GPGPassphrasePanel.h
//  GPGAppKit
//
//  Copyright (C) 2001-2003 Mac GPG Project.
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

#import <AppKit/AppKit.h>
#import "GPGAppKitDefines.h"


@interface GPGPassphrasePanelController : NSWindowController {
    @private
    IBOutlet NSTextField * promptTextField;
    IBOutlet NSTextField * titleTextField;
    IBOutlet NSSecureTextField * passphraseTextField;
    IBOutlet NSButtonCell * okButton;
    BOOL okPressed;
    BOOL sheetOpen;
}

+ (id) sharedPassphrasePanelController;
+ (id) passphrasePanelController;

- (void) resetToDefaults;

- (void) setTitle: (NSString *) title;
- (NSString *) title;

- (void) setPrompt: (NSString *) prompt;
- (NSString *) prompt;

- (void) beginSheetWithPrompt: (NSString *) prompt
               modalForWindow: (NSWindow *) window
                modalDelegate: (id) delegate
               didEndSelector: (SEL) endSelector
                  contextInfo: (id) info;
- (BOOL) runModalWithPrompt: (NSString *) prompt;
//deprecated fucntion, use at own risk
- (BOOL) runModalWithPrompt: (NSString *) prompt relativeToWindow: (NSWindow *) window;

- (NSString *) passphrase;

- (IBAction)cancel:(id)sender;
- (IBAction)ok:(id)sender;
@end
