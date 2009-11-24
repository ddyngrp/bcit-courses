//
//  PKInspectorController.h
//  GPG Keychain Access
//
//  Created by Gordon Worley on Thu May 23 2002.
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
#import "PKController.h"
#import "PKLocalisableStrings.h"

@interface PKInspectorController : NSWindowController
{
    GPGKey *key;
    NSDictionary *key_info;
    
    IBOutlet NSTextField
        //primary key tab fields
        *prim_userid,
		*prim_keyid,
		*prim_algo,
		*prim_len,
		*prim_validity,
		*prim_cdate,
		*prim_edate,
		*prim_expired,
        *prim_disabled,
		*prim_invalid,
		*prim_revoked,
		*prim_finger,
        //subkey tab fields
        *sub_keyid,
		*sub_algo,
		*sub_len,
		*sub_cdate,
		*sub_edate,
		*sub_expired,
		*sub_disabled,
		*sub_invalid,
        *sub_revoked,
        //user ID tab fields
        *user_name,
		*user_email,
		*user_comment,
		*user_validity,
		*user_invalid,
		*user_revoked;
    IBOutlet NSPopUpButton
		*subkeys_menu,
		*userids_menu;
    IBOutlet NSImageView	*photo;
	IBOutlet NSTabView		*keyPropertiesTabs;
    IBOutlet NSOutlineView	*pkOutline;
	IBOutlet PKController	*pkController;

}
- (void)update;
- (void)setKey: (GPGKey *)new_key;
- (GPGKey *)key;
- (void)setSubKeys: (NSArray *)subkeys;
- (void)setUserIDs: (NSArray *)userids;

- (IBAction)changeSubKey: (id)sender;
- (IBAction)changeUserID: (id)sender;
- (IBAction)showWindow: (id)sender;

- (BOOL)validateToolbarItem:(NSToolbarItem *)theItem;

@end