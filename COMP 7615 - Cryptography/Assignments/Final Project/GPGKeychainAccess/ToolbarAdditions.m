//
//  ToolbarAdditions.m
//  GPG Keychain Access
//
//  Created by Randall Wood on Mon Jun 23 2003.
//  Copyright (c) 2003 MacGPG Project. All rights reserved.
//

#import "ToolbarAdditions.h"
#import <Foundation/Foundation.h>

@implementation NSToolbar (CHToolbarCustomizableAdditions)

- (BOOL) alwaysCustomizableByDrag
{
	return (BOOL) _tbFlags.clickAndDragPerformsCustomization;
}

- (void) setAlwaysCustomizableByDrag:(BOOL) flag
{
	_tbFlags.clickAndDragPerformsCustomization = (unsigned int) flag & 1;
}

- (BOOL) showsContextMenu
{
	return (BOOL) ! _tbFlags.showsNoContextMenu;
}

- (void) setShowsContextMenu:(BOOL) flag
{
	_tbFlags.showsNoContextMenu = (unsigned int) ! flag & 1;
}

- (unsigned int) indexOfFirstMovableItem
{
	return (unsigned int) _tbFlags.firstMoveableItemIndex;
}

- (void)setIndexOfFirstMovableItem:(unsigned int)anIndex
{
	_tbFlags.firstMoveableItemIndex = (unsigned int) anIndex & 0x3F;
}

@end
