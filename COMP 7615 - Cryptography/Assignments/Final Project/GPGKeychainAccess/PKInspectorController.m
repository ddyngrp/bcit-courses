//
//  PKInspectorController.m
//  GPG Keychain Access
//
//  Created by Gordon Worley on Thur May 23 2002.
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

#import "PKInspectorController.h"

@implementation PKInspectorController

- (void)awakeFromNib
{
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(outlineViewSelectionDidChange:)
                                                 name:NSOutlineViewSelectionDidChangeNotification object:pkOutline];
}

- (IBAction)showWindow: (id)sender
{
	if (4 == [keyPropertiesTabs numberOfTabViewItems]) {
		[keyPropertiesTabs removeTabViewItem:
			[keyPropertiesTabs tabViewItemAtIndex:
				([keyPropertiesTabs numberOfTabViewItems] - 1)]];
	}
    [[self window] orderFront: self];
}

- (void)update
{
    if (nil != key)	{
        NSTask *photo_task;
        NSMutableArray *args;
        int i;
        BOOL has_photo = NO;
        
        //NSLog(@"%@", [key userID]);

        //primary key tab
        
        [prim_userid setStringValue: [key userID]];
        [prim_keyid setStringValue: [key keyID]];
        [prim_algo setStringValue: [key algorithmDescription]];
        [prim_len setIntValue: (int)[key length]];
        [prim_validity setStringValue: [key validityDescription]];
        [prim_cdate setObjectValue: [key creationDate]];
        if ([key_info objectForKey: @"expire"])
            [prim_edate setStringValue: [key_info objectForKey: @"expire"]];
        else
            [prim_edate setStringValue: NSLocalizedString(PKDoesNotExpire, PKDoesNotExpire)];
        [prim_expired setStringValue: [PKLocalizableStrings yesOrNo:[key hasKeyExpired]]];
        [prim_disabled setStringValue: [PKLocalizableStrings yesOrNo:[key isKeyDisabled]]];
        [prim_invalid setStringValue: [PKLocalizableStrings yesOrNo:[key isKeyInvalid]]];
        [prim_revoked setStringValue: [PKLocalizableStrings yesOrNo:[key isKeyRevoked]]];
        [prim_finger setStringValue: [key formattedFingerprint]];

        //subkey tab

        [self setSubKeys: [key subkeys]];

        //user id tab

        [self setUserIDs: [key userIDs]];

		/* comment out all photo code
        //photo tab
        //gpg --photo-viewer 'cat %i > macgpg-photo.jpeg' --show-photos --list-keys [keyid]

        //check to make sure there's a photo
//        NSLog(@"%@", [key names]);
        for (i = 0; i < [[key names] count]; i++)
        {
//            NSLog(@"%@", [[key names] objectAtIndex: i]);
            if ([[[key names] objectAtIndex: i] hasPrefix: @"[jpeg image of size"] || [[[key names] objectAtIndex: i] hasPrefix: @"[image of size"])
                has_photo = YES;
        }

        if (has_photo)
        {
            photo_task = [[NSTask alloc] init];

//            NSLog(@"Showing photo");
    
            NS_DURING
                args = [NSMutableArray array];
        
                [args addObject: @"--photo-viewer"];
                [args addObject: @"cat %i > /tmp/macgpg-photo.jpeg"];
                [args addObject: @"--show-photos"];
                [args addObject: @"--list-keys"];
                [args addObject: [key keyID]];
        
                [photo_task setLaunchPath: @"/usr/local/bin/gpg"];
                [photo_task setArguments: args];
        
                [photo_task launch];
                [photo_task waitUntilExit];
                [photo setImage: [[[NSImage alloc] initWithContentsOfFile: @"/tmp/macgpg-photo.jpeg"] autorelease]];
            NS_HANDLER
                NSLog(@"Something happened with the photo:  %@", localException);
            NS_ENDHANDLER
            [photo_task release];
        }
        else
        {
			// this crashes badly and consistently. Why?
            [photo setImage: nil];
            NSLog(@"Not showing photo");
        }
		*/
    }
}

- (void)setKey:(GPGKey *)new_key
{
    new_key = [new_key copy];
    [key release];
    key = new_key;
    [key_info release];
    key_info = [[key dictionaryRepresentation] retain];
}

- (GPGKey *)key
{
    return key;
}

- (void)setSubKeys: (NSArray *)subkeys
{
	NSMutableArray *subkeyIDs;
	NSObject *item;
	NSEnumerator *enumerator;

	subkeyIDs = [NSMutableArray arrayWithCapacity:[subkeys count]];
	enumerator = [subkeys objectEnumerator];
	
	while (item = [enumerator nextObject]) {
		[subkeyIDs addObject:[item keyID]];
	}
	
    [subkeys_menu removeAllItems];
    [subkeys_menu addItemsWithTitles: subkeyIDs];

    [self changeSubKey: self];
}

- (void)setUserIDs: (NSArray *)userids
{
	NSMutableArray *userIDUserIDs;
	NSObject *item;
	NSEnumerator *enumerator;
	
	userIDUserIDs = [NSMutableArray arrayWithCapacity:[userids count]];
	enumerator = [userids objectEnumerator];
	
	while (item = [enumerator nextObject]) {
		[userIDUserIDs addObject:[item description]];
	}
	
    [userids_menu removeAllItems];
    [userids_menu addItemsWithTitles: userIDUserIDs];

    [self changeUserID: self];
}

- (IBAction)changeSubKey: (id)sender
{
    int index;
    NSDictionary *subkey_info;
    
    index = [subkeys_menu indexOfSelectedItem];
    if (index > -1)	{
        subkey_info = [[key_info objectForKey: @"subkeys"] objectAtIndex: index];
        [sub_keyid setStringValue: [subkey_info objectForKey: @"keyid"]];
        [sub_algo setStringValue: GPGPublicKeyAlgorithmDescription([[subkey_info objectForKey: @"algo"] intValue])];
        [sub_len setStringValue: [subkey_info objectForKey: @"len"]];
        [sub_cdate setStringValue: [subkey_info objectForKey: @"created"]];
        if ([[subkey_info objectForKey: @"expire"] isKindOfClass:[NSDate class]])	{
            //NSLog(@"%@", [[subkey_info objectForKey: @"expire"] class]);
            [sub_edate setStringValue: [subkey_info objectForKey: @"expire"]];
        }
        else
            [sub_edate setStringValue: NSLocalizedString(PKDoesNotExpire, PKDoesNotExpire)];
        [sub_expired setStringValue: [PKLocalizableStrings yesOrNo:[[subkey_info objectForKey: @"expired"] intValue]]];
        [sub_disabled setStringValue: [PKLocalizableStrings yesOrNo:[[subkey_info objectForKey: @"disabled"] intValue]]];
        [sub_invalid setStringValue: [PKLocalizableStrings yesOrNo:[[subkey_info objectForKey: @"invalid"] intValue]]];
        [sub_revoked setStringValue: [PKLocalizableStrings yesOrNo:[[subkey_info objectForKey: @"revoked"] intValue]]];
    }
    else	{
        [sub_keyid setStringValue: @""];
        [sub_algo setStringValue: @""];
        [sub_len setStringValue: @""];
        [sub_cdate setStringValue: @""];
        [sub_edate setStringValue: @""];
        [sub_expired setStringValue: @""];
        [sub_disabled setStringValue: @""];
        [sub_invalid setStringValue: @""];
        [sub_revoked setStringValue: @""];
    }    
}

- (IBAction)changeUserID: (id)sender
{
    int index;
    NSDictionary *userid_info;

    index = [userids_menu indexOfSelectedItem];
    if (index > -1)	{
        userid_info = [[key_info objectForKey: @"userids"] objectAtIndex: index];
        [user_name setStringValue: [userid_info objectForKey: @"name"]];
        [user_email setStringValue: [userid_info objectForKey: @"email"]];
        [user_comment setStringValue: [userid_info objectForKey: @"comment"]];
        [user_validity setStringValue: GPGValidityDescription([[userid_info objectForKey: @"validity"] intValue])];
        [user_invalid setStringValue: [PKLocalizableStrings yesOrNo:[[userid_info objectForKey: @"invalid"] intValue]]];
        [user_revoked setStringValue: [PKLocalizableStrings yesOrNo:[[userid_info objectForKey: @"revoked"] intValue]]];
    }
    else	{
        [user_name setStringValue: @""];
        [user_email setStringValue: @""];
        [user_comment setStringValue: @""];
        [user_validity setStringValue: @""];
        [user_invalid setStringValue: @""];
        [user_revoked setStringValue: @""];        
    }
}

- (void)outlineViewSelectionDidChange:(NSNotification *)notification
{
    if ([[notification object] isEqual:pkOutline] && [pkOutline numberOfSelectedRows] == 1) {
        GPGContext *context = [[GPGContext alloc] init];
        [self setKey:[[[context keyEnumeratorForSearchPattern: [[pkOutline itemAtRow: [pkOutline selectedRow]] objectForKey: @"shortkeyid"] secretKeysOnly: NO] allObjects] objectAtIndex: 0]];
        [context release];
    } else {
        [self setKey:nil];
	}
    [self update];
}

/*
 * Since PKInspectorController is the target for these toolbar items,
 * PKInspectorController must validate these items.
 */
- (BOOL)validateToolbarItem:(NSToolbarItem *)theItem
{
	if ([pkOutline numberOfSelectedRows] != 1 &&
		[theItem action] == @selector(showWindow:)) {
		return NO;
	}
	return YES;
}

@end
