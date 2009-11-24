//
//  GPGDocument_IBActions.m
//  GPGFileTool
//
//  Created by Gordon Worley.
//  Copyright (C) 2002 Mac GPG Project.
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

#import "GPGDocument.h"
#import "LocalizableStrings.h"

@implementation GPGDocument (IBActions)

- (IBAction)doIt:(id)sender
{
    NSData *returned_data = nil;
    NSString *returned_type = nil;
    //NSLog(@"%d", [actionList indexOfSelectedItem]);

    [gpgData rewind];  //make sure it's at the begining so that we don't get No Data errors

    switch ([actionList indexOfSelectedItem])	{
        case GPGFTEncryptAndSign:
            returned_data = [self encryptAndSign];
            returned_type = @"Encrypted & Signed file";
            break;
        case GPGFTEncrypt:
            returned_data = [self encrypt];
            returned_type = @"Encrypted file";
            break;
        case GPGFTSign:
            returned_data = [self sign];
            returned_type = @"Signed file";
            break;
        case GPGFTSignDetached:
            returned_data = [self signDetached];
            returned_type = @"Detached signature";
            break;
        case GPGFTClearsign:
            returned_data = [self clearsign];
            returned_type = @"Clearsigned file";
            break;
        case GPGFTSymmetricallyEncrypt:
            returned_data = [self symmetricallyEncrypt];
            returned_type = @"Symmetrically Encrypted file";
            break;
            //case 5 is the separator
        case GPGFTDecryptAndVerify:
            returned_data = [self decryptAndVerify];
            returned_type = @"Data";
            break;
        case GPGFTDecrypt:
            returned_data = [self decrypt];
            returned_type = @"Data";
            break;
        case GPGFTVerify:
            returned_data = [self verify];
            returned_type = @"Data";
            break;
        case GPGFTVerifyDetached:
            returned_data = [self verifyDetached];
            returned_type = @"Data";
            break;
        default:
            NSBeginAlertSheet(@"D'oh", nil, nil, nil, [self window], nil, nil, nil, nil,
                              @"Hey, you can't do that on GPGFileTool.");
            break;
    }
    if (returned_data)	{
        BOOL wrote_file = NO;
        wrote_file = [self writeFileWithData: returned_data ofType: returned_type];
        if (wrote_file)	{
            if ([ckbox_showAfter state] == NSOnState)
                [self showInFinder: outFilename];
            if ([ckbox_openAfter state] == NSOnState)
                [self openFileWithFilename: outFilename];
            if ([ckbox_deleteOriginal state] == NSOnState)
                [self deleteOriginalFile];
        }
    }
}

- (IBAction)openFile:(id)sender
{
    [self openFileWithFilename: [self fileName]];
}

- (IBAction)showFileInFinder:(id)sender
{
    [self showInFinder: [self fileName]];
}

- (IBAction)actionSelectionChanged: (id)sender
//disable/enable options as appropriate
{
    switch ([actionList indexOfSelectedItem])	{
        case GPGFTEncryptAndSign:
            [ckbox_armored setEnabled: YES];
            [ckbox_openAfter setEnabled: YES];
            [ckbox_showAfter setEnabled: YES];
            [ckbox_deleteOriginal setEnabled: YES];
            break;
        case GPGFTEncrypt:
            [ckbox_armored setEnabled: YES];
            [ckbox_openAfter setEnabled: YES];
            [ckbox_showAfter setEnabled: YES];
            [ckbox_deleteOriginal setEnabled: YES];
            break;
        case GPGFTSign:
            [ckbox_armored setEnabled: YES];
            [ckbox_openAfter setEnabled: YES];
            [ckbox_showAfter setEnabled: YES];
            [ckbox_deleteOriginal setEnabled: NO];
            break;
        case GPGFTSignDetached:
            [ckbox_armored setEnabled: YES];
            [ckbox_openAfter setEnabled: YES];
            [ckbox_showAfter setEnabled: YES];
            [ckbox_deleteOriginal setEnabled: NO];
            break;
        case GPGFTClearsign:
            [ckbox_armored setEnabled: YES];
            [ckbox_openAfter setEnabled: YES];
            [ckbox_showAfter setEnabled: YES];
            [ckbox_deleteOriginal setEnabled: NO];
            break;
        case GPGFTSymmetricallyEncrypt:
            [ckbox_armored setEnabled: YES];
            [ckbox_openAfter setEnabled: YES];
            [ckbox_showAfter setEnabled: YES];
            [ckbox_deleteOriginal setEnabled: YES];
            break;
        //Separator
        case GPGFTDecryptAndVerify:
            [ckbox_armored setEnabled: NO];
            [ckbox_openAfter setEnabled: YES];
            [ckbox_showAfter setEnabled: YES];
            [ckbox_deleteOriginal setEnabled: NO];
            break;
        case GPGFTDecrypt:
            [ckbox_armored setEnabled: NO];
            [ckbox_openAfter setEnabled: YES];
            [ckbox_showAfter setEnabled: YES];
            [ckbox_deleteOriginal setEnabled: NO];
            break;
        case GPGFTVerify:
            [ckbox_armored setEnabled: NO];
            [ckbox_openAfter setEnabled: NO];
            [ckbox_showAfter setEnabled: NO];
            [ckbox_deleteOriginal setEnabled: NO];
            break;
        case GPGFTVerifyDetached:
            [ckbox_armored setEnabled: NO];
            [ckbox_openAfter setEnabled: NO];
            [ckbox_showAfter setEnabled: NO];
            [ckbox_deleteOriginal setEnabled: NO];
            break;
        default:
            [ckbox_armored setEnabled: YES];
            [ckbox_openAfter setEnabled: YES];
            [ckbox_showAfter setEnabled: YES];
            [ckbox_deleteOriginal setEnabled: YES];
            
            NSBeginAlertSheet(@"D'oh", nil, nil, nil, [self window], nil, nil, nil, nil,
                              @"Hey, you can't do that on GPGFileTool.");
            break;
    }    
}

@end