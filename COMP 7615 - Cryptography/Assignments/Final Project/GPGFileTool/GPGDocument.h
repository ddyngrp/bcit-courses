//
//  GPGDocument.h
//  GPGFileTool
//
//  Created by Gordon Worley on Wed Mar 27 2002.
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

#import <Cocoa/Cocoa.h>
#import <MacGPGME/MacGPGME.h>

typedef enum
{
    GPGFTEncryptAndSign			= 0,
    GPGFTEncrypt				= 1,
    GPGFTSign					= 2,
    GPGFTSignDetached			= 3,
    GPGFTClearsign				= 4,
    GPGFTSymmetricallyEncrypt	= 5,
    GPGFTSeparator				= 6,
    GPGFTDecryptAndVerify		= 7,
    GPGFTDecrypt				= 8,
    GPGFTVerify					= 9,
    GPGFTVerifyDetached			= 10
} GPGFTActionType;

@interface GPGDocument : NSDocument
{
    NSUserDefaults *defaults;
    GPGData *gpgData;
    NSDictionary *types;
    NSString *outFilename;
    
    IBOutlet NSTextField *pathToFile;
    IBOutlet NSButton
        *ckbox_armored,
        *ckbox_openAfter,
        *ckbox_showAfter,
        *ckbox_deleteOriginal;
    IBOutlet NSPopUpButton *actionList;
}

- (BOOL)writeFileWithData: (NSData *)data ofType: (NSString *)type;
- (NSData *)dataForDetachedSignature;

@end

@interface GPGDocument (IBActions)

- (IBAction)doIt: (id)sender;
- (IBAction)openFile: (id)sender;
- (IBAction)showFileInFinder: (id)sender;
- (IBAction)actionSelectionChanged: (id)sender;

@end

@interface GPGDocument (GnuPGActions)

- (GPGRecipients *)getRecipient;
- (GPGRecipients *)getRecipients;
- (NSEnumerator *)getSigner;
- (NSEnumerator *)getSigners;
- (void)showVerificationStatus: (NSArray *)signatures;

- (NSData *)encryptAndSign;
- (NSData *)encrypt;
- (NSData *)sign;
- (NSData *)signDetached;
- (NSData *)clearsign;
- (NSData *)symmetricallyEncrypt;

- (NSData *)decryptAndVerify;
- (NSData *)decrypt;
- (NSData *)verify;
- (NSData *)verifyDetached;

@end

@interface GPGDocument (Utility)

- (NSWindow *)window;
- (void)handleException: (NSException *)exception;
- (void)openFileWithFilename: (NSString *)filename;
- (void)showInFinder: (NSString *)filename;
- (void)deleteOriginalFile;

@end