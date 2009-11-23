//
//  GPGFTController.h
//  GPGFileTool
//
//  Created by Gordon Worley on Wed Mar 27 2002.
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


/*
 UserDefaults:

 - user_default_action: (int) index of default action from action popup menu in GPGDocument.nib
 - default_armored: (BOOL) whether to check to armor check box by default
 - default_open_after: (BOOL) whether to open document after acting on it by default
 - default_open_unless_ciphered: (BOOL) whether it should open up a file just after it's been gpg'd (most likely in Mac GPG)
 - default_show_after: (BOOL) whether to show the file in the Finder after acting on it by default
 - default_decrypt_and_verify: (BOOL) whether to decrypt and verify by default (rather than decyrypt only)
 - select_single_recipient: (BOOL) display single recipient selection panel
 - select_single_singer: (BOOL) display single signer selection panel
 - list_all_uids: (BOOL) should list all user IDs for single key selection panels
 - warn_before_delete: (BOOL) give the user one last chance to not delete original
 - activation_behavior: (int) take an action from GPGFTActivationBehavior upon activation
*/

#import <Cocoa/Cocoa.h>
#import "GPGPrefController.h"

@interface GPGFTController : NSObject
{
    //NSUserDefaults *defaults;

    GPGPrefController *prefController;

    IBOutlet NSMenu *fileMenu;
}

- (IBAction)showPrefs: (id)sender;
- (IBAction)showGPGPrefs: (id)sender;

@end
