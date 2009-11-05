//
//  GPGSingleKeySelectionPanelController.m
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
#import "GPGSingleKeySelectionPanelController.h"
#import "GPGAppKitDefines.h"

static GPGSingleKeySelectionPanelController * sharedGPGSingleKeySelectionPanel = nil;

@interface GPGSingleKeySelectionPanelController (Private)

- (void) displayKeys;

@end

@implementation GPGSingleKeySelectionPanelController

+ (id) sharedSingleKeySelectionPanelController
{
    if (sharedGPGSingleKeySelectionPanel == nil)
        sharedGPGSingleKeySelectionPanel =
            [[[GPGSingleKeySelectionPanelController alloc] initWithWindowNibName: @"GPGSingleKeySelectionPanel"] autorelease];
    return sharedGPGSingleKeySelectionPanel;
}

+ (id) singleKeySelectionPanelController
{
    return [[[GPGSingleKeySelectionPanelController alloc] initWithWindowNibName: @"GPGSingleKeySelectionPanel"] autorelease];
}

- (void)awakeFromNib
{
    [super awakeFromNib];
    
    [keySelector setAutoenablesItems: NO];
    [self resetToDefaults];
    [self displayKeys];
}

- (void) resetToDefaults {
    NSBundle * mybundle = [NSBundle bundleForClass: [self class]];
    [[self window] setTitle:[mybundle localizedStringForKey:GPGAppKitSingleKeySelectionPanelTitle
                                             value:@"Arse"
                                             table:nil]];
    [self setPrompt:[mybundle localizedStringForKey:GPGAppKitSingleKeySelectionPanelPrompt
                                              value:@"Arse"
                                              table:nil]];
    [self setListsSecretKeys: NO];
    [self setListsAllUserIDs: NO];
    [self setOkPressed: NO];
}

- (void) resetKeyListForWildcard: (NSString *) wildcard
                    usingContext: (GPGContext *) context
//parent figures out what keys to display
//this is just the code to display them
{    
    [super resetKeyListForWildcard: wildcard
                      usingContext: context];
    [self displayKeys];
}

- (void) displayKeys
{
    int i;
    NSEnumerator *nameEnumerator;
    NSString *name;
    
    [keySelector removeAllItems];

    for (i = 0; i < [keys count]; i++)
    {
        [keySelector addItemWithTitle: [[keys objectAtIndex: i] userID]];

        if ([self listsAllUserIDs])
        {
            nameEnumerator = [[[keys objectAtIndex: i] userIDs] objectEnumerator];
            [nameEnumerator nextObject]; //eat the primary uid since it's already listed
            while (name = [nameEnumerator nextObject]) {
                [keys insertObject: [keys objectAtIndex: i] atIndex: i];
                i++;
                [keySelector addItemWithTitle: [NSString stringWithFormat: @"    %@", name]];
                [[keySelector itemAtIndex: i] setEnabled: NO];
            }
        }
    }    
}

- (GPGKey *) selectedKey
{
    if ([self okPressed]) {
        return [[self keys] objectAtIndex: [keySelector indexOfSelectedItem]];
    } else {
        return nil;
    }
}

- (void) setPrompt: (NSString *) prompt
{
    [promptTextField setStringValue:prompt];
}

- (NSString *) prompt
{
    return [promptTextField stringValue];
}

- (void) setListsAllUserIDs: (BOOL) yesNo
{
    listsAllUserIDs = yesNo;
}

- (BOOL) listsAllUserIDs
{
    return listsAllUserIDs;
}

@end
