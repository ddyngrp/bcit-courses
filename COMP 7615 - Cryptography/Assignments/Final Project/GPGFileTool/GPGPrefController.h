//
//  GPGPrefController.h
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


#import <Cocoa/Cocoa.h>

typedef enum
{
    GPGFT_ABOpen = 0,
    GPGFT_ABDoNothing = 1,
    GPGFT_ABOpenLaunchOnly = 2
} GPGFTActivationBehavior;

@interface GPGPrefController : NSWindowController
{
    NSUserDefaults *defaults;
    
    IBOutlet NSButton
        *ckbox_armored,
        *ckbox_decryptAndVerify,
        *ckbox_openAfter,
        *ckbox_openUnlessCipher,
        *ckbox_showAfter,
        *ckbox_singleRecipient,
        *ckbox_singleSigner,
        *ckbox_deleteOriginal,
        *ckbox_warnBeforeDelete,
        *ckbox_listAllUIDs;
    IBOutlet NSMatrix *activationBehaviors;
    IBOutlet NSPopUpButton *actionList;
}

- (IBAction)apply: (id)sender;
- (IBAction)openAfterChanged: (id)sender;

@end
