//
//  ToolbarAdditions.h
//  GPG Keychain Access
//
//  Created by Randall Wood on Mon Jun 23 2003.
//  Copyright (c) 2003 MacGPG Project. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AppKit/NSToolbar.h>

@interface NSToolbar (PKToolbarCustomizableAdditions)

- (BOOL)alwaysCustomizableByDrag;
- (void)setAlwaysCustomizableByDrag:(BOOL) flag;

- (BOOL)showsContextMenu;
- (void)setShowsContextMenu:(BOOL) flag;

- (unsigned int)indexOfFirstMovableItem;
- (void)setIndexOfFirstMovableItem:(unsigned int) anIndex;

@end
