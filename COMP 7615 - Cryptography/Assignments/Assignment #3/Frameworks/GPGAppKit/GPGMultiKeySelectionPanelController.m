//
//  GPGMultiKeySelectionPanelController.m
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
#import "GPGMultiKeySelectionPanelController.h"
#ifdef USE_OMNI
#import <OmniAppKit/OmniAppKit.h>
#endif

static GPGMultiKeySelectionPanelController * sharedGPGMultiKeySelectionPanel = nil;

@implementation GPGMultiKeySelectionPanelController

+ (id) sharedMultiKeySelectionPanelController
{
    if (sharedGPGMultiKeySelectionPanel == nil)
        sharedGPGMultiKeySelectionPanel =
            [[[GPGMultiKeySelectionPanelController alloc] initWithWindowNibName: @"GPGMultiKeySelectionPanel"] autorelease];
    return sharedGPGMultiKeySelectionPanel;
}

+ (id) multiKeySelectionPanelController
{
    return [[[GPGMultiKeySelectionPanelController alloc] initWithWindowNibName: @"GPGMultiKeySelectionPanel"] autorelease];
}

- (void)awakeFromNib
{
    [super awakeFromNib];
    
    [self resetToDefaults];
}

- (void) resetToDefaults {
    [self setListsSecretKeys:NO];
    [self setOkPressed:NO];
    [self setListsAllSubkeys: YES];
    [keySelector deselectAll: nil];
    [keySelector setDelegate: self];
    [keySelector setDataSource: self];
    [keySelector setTarget: self];

}

- (void) resetKeyListForWildcard: (NSString *) wildcard
                    usingContext: (GPGContext *) context
{
    [super resetKeyListForWildcard: wildcard
                      usingContext: context];
    [keySelector reloadData];
    [keySelector setNeedsDisplay: YES];
}

- (int)numberOfRowsInTableView: (NSTableView *) aTableView
{
    return [keys count];
}

- (id)tableView:(NSTableView *)aTableView objectValueForTableColumn:(NSTableColumn *)aTableColumn row:(int)rowIndex
{
    if ([[aTableColumn identifier] isEqualTo: @"keyinfo"])
    {
        return [[keys objectAtIndex: rowIndex] userID];
    }
    else if ([[aTableColumn identifier] isEqualTo: @"keyid"])
    {
        return [[keys objectAtIndex: rowIndex] shortKeyID];
    }
    else
        return @"error";
}
#ifdef USE_OMNI
- (NSString *)tableView:(NSTableView *)tableView tooltipForRow:(int)row column:(int)column
{
    NSMutableString *tooltip = [NSMutableString string];
    int i;
    NSArray *userids = [[keys objectAtIndex: row] userIDs];
    
    for (i = 0; i < [userids count] - 1; i++)
    {
        [tooltip appendString: [userids objectAtIndex: i]];
        [tooltip appendString: @"\n"];
    }
    [tooltip appendString: [userids objectAtIndex: i]];
    
    return tooltip;
}
#endif

- (NSArray *) selectedKeys {
    if ([self okPressed] && [keySelector numberOfSelectedRows]) {
        NSMutableArray * selectedKeys = [NSMutableArray array];
        NSEnumerator * enumerator = [keySelector selectedRowEnumerator];
        id object;
        while (object = [enumerator nextObject]) {
            [selectedKeys addObject:[[self keys] objectAtIndex:[object intValue]]];
        }
        return selectedKeys;
    }
    else
        return nil;
}

- (void)setPrompt: (NSString *)newPrompt
{
    [promptTextField setStringValue: newPrompt];
}

- (NSString *)prompt
{
    return [promptTextField stringValue];
}

- (void)setListsAllSubkeys: (BOOL)yesNo
{
    listsAllSubkeys = yesNo;
}

- (BOOL)listsAllSubkeys
{
    return listsAllSubkeys;
}

@end
