//
//  GPGKeySelectionPanelController.h
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
#import <MacGPGME/MacGPGME.h>

@interface GPGKeySelectionPanelController : NSWindowController {
  @protected

  BOOL okPressed;
  BOOL listsSecretKeys;
  NSMutableArray * keys;
  id _keyFilter;
  id _contextInfo;
}

- (BOOL) okPressed;
- (void) setOkPressed: (BOOL) yesNo;
- (BOOL) listsSecretKeys;
- (void) setListsSecretKeys: (BOOL) yesNo;

- (void) setKeyFilter: (id)keyFilter;
- (id) keyFilter;
- (void) setContextInfo: (id)info;
- (id) contextInfo;

- (void) beginSheetForKeyWildcard: (NSString *) wildcard
                     usingContext: (GPGContext *) context
                   modalForWindow: (NSWindow *) window
                    modalDelegate: (id) delegate
                   didEndSelector: (SEL) endSelector
                      contextInfo: (id) info;
- (BOOL) runModalForKeyWildcard: (NSString *) wildcard
                   usingContext: (GPGContext *) aContext;
//deprecated fucntion, use at own risk
- (BOOL) runModalForKeyWildcard: (NSString *) wildcard
                   usingContext: (GPGContext *) aContext
               relativeToWindow: (NSWindow *) window;

- (void) resetKeyListForWildcard: (NSString *) wildcard
                    usingContext: (GPGContext *) context;

- (IBAction) cancel: (id) sender;
- (IBAction) ok: (id) sender;

- (NSArray *) keys;

@end

@interface NSObject (GPGKeySelectionPanelControllerKeyFilter)

- (BOOL)shouldDisplayKey: (GPGKey *)key contextInfo: (id)info;

@end
