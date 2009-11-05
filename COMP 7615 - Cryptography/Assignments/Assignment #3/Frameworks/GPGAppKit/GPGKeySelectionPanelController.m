//
//  GPGKeySelectionPanelController.m
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

#import "GPGKeySelectionPanelController.h"


@implementation GPGKeySelectionPanelController

- (void) awakeFromNib
{
    _keyFilter = nil;
    _contextInfo = nil;
}

- (void) dealloc {
    [keys release];
    [_keyFilter release];
    [_contextInfo release];
    [super dealloc];
}

- (void) setListsSecretKeys: (BOOL) yesNo {
    listsSecretKeys = yesNo;
}

- (void) setKeyFilter: (id)keyFilter
{
    [keyFilter retain];
    [_keyFilter release];
    _keyFilter = keyFilter;
}

- (id) keyFilter
{
    return _keyFilter;
}

- (void) setContextInfo: (id)info
{
    [info retain];
    [_contextInfo release];
    _contextInfo = info;
}

- (id) contextInfo
{
    return _contextInfo;
}

- (void) beginSheetForKeyWildcard: (NSString *) wildcard
                     usingContext: (GPGContext *) context
                   modalForWindow: (NSWindow *) parentWindow
                    modalDelegate: (id) delegate
                   didEndSelector: (SEL) endSelector
                      contextInfo: (id) info
{
    [self resetKeyListForWildcard: wildcard
                     usingContext: context];

    [NSApp beginSheet: [self window]
       modalForWindow: parentWindow
        modalDelegate: delegate
       didEndSelector: endSelector
          contextInfo: info];
}



- (BOOL) runModalForKeyWildcard: (NSString *) wildcard
                   usingContext: (GPGContext *) context
{
    [self resetKeyListForWildcard: wildcard
                     usingContext: context];

    [NSApp runModalForWindow: [self window]];

    if (okPressed)
        return NSOKButton;
    else
        return NSCancelButton;
}

//deprecated fucntion, use at own risk
//I needed it, but you should try to not use it.
- (BOOL) runModalForKeyWildcard: (NSString *) wildcard
                   usingContext: (GPGContext *) context
               relativeToWindow: (NSWindow *) parentWindow
{
    [self resetKeyListForWildcard: wildcard
                     usingContext: context];

    [NSApp runModalForWindow: [self window] relativeToWindow: parentWindow];

    if (okPressed)
        return NSOKButton;
    else
        return NSCancelButton;
}

- (void) cancel: (id) sender {
    if ([[self window] isSheet]) {
        [NSApp endSheet: [self window]];
    } else {
        [NSApp stopModal];
    }

    okPressed = NO;
    [[self window] orderOut: nil];
}

- (void) ok: (id) sender {
    if ([[self window] isSheet]) {
        [NSApp endSheet: [self window]];
    } else {
        [NSApp stopModal];
    }

    okPressed = YES;
    [[self window] orderOut: nil];
}

- (void) resetKeyListForWildcard: (NSString *) wildcard
                    usingContext: (GPGContext *) context
{
    //we reassign these variables so that we can easily handle the case when they are nil
    GPGContext * theContext = [context retain];
    NSString * theWildcard = [wildcard retain];
    NSEnumerator * keyEnumerator;
    GPGKey *key;

    if (!keys)
        keys = [[NSMutableArray alloc] init];

    // Allocate autoreleased context and wildcard if not passed in
    if (!theContext) theContext = [[GPGContext alloc] init];
    if (!theWildcard) theWildcard = [[NSString alloc] initWithString: @""];

    [keys removeAllObjects];

    keyEnumerator = [theContext keyEnumeratorForSearchPattern:theWildcard
                                               secretKeysOnly:listsSecretKeys];

    while (key = [keyEnumerator nextObject])
    {
        if ([_keyFilter respondsToSelector: @selector(shouldDisplayKey:contextInfo:)])
        {
            //NSLog(@"key filter delegate");
            if ([_keyFilter shouldDisplayKey: key contextInfo: _contextInfo])
            {
                //NSLog(@"Adding a key");
                [keys addObject: key];
            }
        }
        else
            [keys addObject: key];
    }

    [theContext release];
    [theWildcard release];

    //NSLog(@"keys parent: %@", keys);
}

- (NSArray *) keys {
    return keys;
}

- (BOOL) listsSecretKeys {
    return listsSecretKeys;
}
- (BOOL) okPressed {
    return okPressed;
}
- (void) setOkPressed: (BOOL) yesNo {
    okPressed = yesNo;
}

@end
