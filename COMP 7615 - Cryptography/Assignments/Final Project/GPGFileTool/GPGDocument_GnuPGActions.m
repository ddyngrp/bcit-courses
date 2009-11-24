//
//  GPGDocument_GnuPGActions.m
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

@implementation GPGDocument (GnuPGActions)

- (NSString *) context:(GPGContext *)context passphraseForKey:(GPGKey *)key again:(BOOL)again
{
    GPGPassphrasePanel *ppanel = [GPGPassphrasePanel panel];
    BOOL pressedOK;

    if (key)  //Asymmetric encryption
    {
        if (again)
        {
            pressedOK = [ppanel runModalWithPrompt: [NSString stringWithFormat:
                NSLocalizedString(FTEnterPassphraseAgainPrompt, nil), [key userID], [key shortKeyID]]
                                  relativeToWindow: [self window]];
        }
        else
        {
            pressedOK = [ppanel runModalWithPrompt: [NSString stringWithFormat:
                NSLocalizedString(FTEnterPassphrasePrompt, nil), [key userID], [key shortKeyID]]
                                  relativeToWindow: [self window]];
        }
    }
    else  //Symmetric encryption
    {
        pressedOK = [ppanel runModalWithPrompt: NSLocalizedString(FTEnterPassphraseForSymmetricKeyPrompt, nil)
                              relativeToWindow: [self window]];
    }

    if (pressedOK == NSCancelButton)
        [[NSException exceptionWithGPGError: GPGErrorCanceled userInfo: nil] raise];

    return [ppanel passphrase];
}

- (GPGRecipients *) getRecipient
{
    GPGContext *context = [[[GPGContext alloc] init] autorelease];
    GPGRecipients *recipients = [[[GPGRecipients alloc] init] autorelease];
    GPGSingleKeySelectionPanel *panel = [GPGSingleKeySelectionPanel panel];
    BOOL gotRecipient;

    // Init the panel
    [panel setKeyFilter: self];
    [panel setContextInfo: @"recipients"];
    [panel setListsSecretKeys: NO];
    [panel setListsAllUserIDs: [defaults boolForKey: @"list_all_uids"]];
    [panel setPrompt: NSLocalizedString(FTGetRecipient, nil)];

    gotRecipient = [panel runModalForKeyWildcard:nil usingContext:context relativeToWindow: [self window]];

    // Populate the recipients
    if (gotRecipient)
        [recipients addName: [[panel selectedKey] fingerprint]];
    else
        recipients = nil;

    return recipients;    
}

- (GPGRecipients *) getRecipients
{
    GPGContext * context = [[[GPGContext alloc] init] autorelease];
    GPGRecipients * recipients = [[[GPGRecipients alloc] init] autorelease];
    GPGMultiKeySelectionPanel * panel = [GPGMultiKeySelectionPanel panel];
    NSEnumerator * enumerator;
    BOOL gotRecipient;
    id object;

    // Init the panel
    [panel setKeyFilter: self];
    [panel setContextInfo: @"recipients"];
    [panel setListsSecretKeys:NO];
    [panel setPrompt: NSLocalizedString(FTGetRecipients, nil)];

    gotRecipient = [panel runModalForKeyWildcard:nil usingContext:context relativeToWindow: [self window]];

    // Populate the recipients
    if (gotRecipient) {
        enumerator = [[panel selectedKeys] objectEnumerator];
        while (object = [enumerator nextObject]) {
            [recipients addName:[object fingerprint]];
        }
    }
    else
        recipients = nil;

    return recipients;
}

- (NSEnumerator *) getSigner
{
    GPGContext * context = [[[GPGContext alloc] init] autorelease];
    GPGSingleKeySelectionPanel * panel = [GPGSingleKeySelectionPanel panel];

    [panel setKeyFilter: self];
    [panel setContextInfo: @"signers"];
    [panel setListsSecretKeys: YES];
    [panel setListsAllUserIDs: [defaults boolForKey: @"list_all_uids"]];
    [panel setPrompt: NSLocalizedString(FTGetSigner, nil)];

    [panel runModalForKeyWildcard:nil usingContext:context relativeToWindow: [self window]];
    return [[NSArray arrayWithObject: [panel selectedKey]] objectEnumerator];
}

- (NSEnumerator *) getSigners
{
    GPGContext *context = [[[GPGContext alloc] init] autorelease];
    GPGMultiKeySelectionPanel *panel = [GPGMultiKeySelectionPanel panel];
    BOOL gotSigners;

    // Init the panel
    [panel setKeyFilter: self];
    [panel setContextInfo: @"signers"];
    [panel setListsSecretKeys: YES];
    [panel setPrompt: NSLocalizedString(FTGetSigners, nil)];

    gotSigners = [panel runModalForKeyWildcard: nil usingContext: context relativeToWindow: [self window]];

    if (gotSigners)
        return [[panel selectedKeys] objectEnumerator];
    else
        return nil;
}

- (void)showVerificationStatus: (NSArray *) signatures
{
    if ([signatures count] == 0)	{
        NSRunInformationalAlertPanelRelativeToWindow(NSLocalizedString(FTSignatureStatus, nil), NSLocalizedString(FTNoSignatureSigStatus, nil), nil, nil, nil, [self window]);
    }
    else if ([signatures count] == 1)	{
        GPGSignature *sig;
        GPGKey *sig_key;
        sig = [signatures objectAtIndex: 0];
        sig_key = [sig key];

        switch ([sig status])	{
            case GPGSignatureStatusGood:
                NSRunInformationalAlertPanelRelativeToWindow(NSLocalizedString(FTSignatureStatus, nil), NSLocalizedString(FTGoodSigStatus, nil), nil, nil, nil, [self window], [sig creationDate], GPGValidityDescription([sig validity]), [sig_key userID], [sig_key fingerprint]);
                break;
            case GPGSignatureStatusBad:
                NSRunInformationalAlertPanelRelativeToWindow(NSLocalizedString(FTSignatureStatus, nil), NSLocalizedString(FTBadSigStatus, nil), nil, nil, nil, [self window], [sig creationDate], GPGValidityDescription([sig validity]), [sig_key userID], [sig_key fingerprint]);
                break;
            case GPGSignatureStatusGoodButExpired:
                NSRunInformationalAlertPanelRelativeToWindow(NSLocalizedString(FTSignatureStatus, nil), NSLocalizedString(FTGoodButExpiredSigStatus, nil), nil, nil, nil, [self window], [sig creationDate], GPGValidityDescription([sig validity]), [sig_key userID], [sig_key fingerprint]);
                break;
            case GPGSignatureStatusGoodButKeyExpired:
                NSRunInformationalAlertPanelRelativeToWindow(NSLocalizedString(FTSignatureStatus, nil), NSLocalizedString(FTGoodButKeyExpiredSigStatus, nil), nil, nil, nil, [self window], [sig creationDate], GPGValidityDescription([sig validity]), [sig_key userID], [sig_key fingerprint]);
                break;
            case GPGSignatureStatusNoKey:
                NSRunInformationalAlertPanelRelativeToWindow(NSLocalizedString(FTSignatureStatus, nil), NSLocalizedString(FTNoKeySigStatus, nil), nil, nil, nil, [self window], [sig fingerprint]);
                break;
            case GPGSignatureStatusNoSignature:
                NSRunInformationalAlertPanelRelativeToWindow(NSLocalizedString(FTSignatureStatus, nil), NSLocalizedString(FTNoSignatureSigStatus, nil), nil, nil, nil, [self window]);
                break;
            default:
                NSRunInformationalAlertPanelRelativeToWindow(NSLocalizedString(FTSignatureStatus, nil), NSLocalizedString(FTErrorSigStatus, nil), nil, nil, nil, [self window]);
                break;
        }
    }
    else	{
        int i;
        //NSMutableArray *keys = [NSMutableArray array];
        NSMutableString *statuses = [NSMutableString string];
        /*
         for (i = 0; i < [signatures count]; i++)	{
             [keys addObject: [(GPGSignature *)[signatures objectAtIndex: i] key]];
         }
         */
        for (i = 0; i < [signatures count]; i++)	{
            if (i > 0)
                [statuses appendString: NSLocalizedString(FTSigSeparator, nil)];
            switch ([[signatures objectAtIndex: i] status])	{
                case GPGSignatureStatusGood:
                    [statuses appendFormat: NSLocalizedString(FTGoodSigStatus, nil), [[signatures objectAtIndex: i] creationDate], GPGValidityDescription([[signatures objectAtIndex: i] validity]), [[(GPGSignature *)[signatures objectAtIndex: i] key] userID], [(GPGSignature *)[signatures objectAtIndex: i] fingerprint]];
                    break;
                case GPGSignatureStatusBad:
                    [statuses appendFormat: NSLocalizedString(FTBadSigStatus, nil), [[signatures objectAtIndex: i] creationDate], GPGValidityDescription([[signatures objectAtIndex: i] validity]), [[(GPGSignature *)[signatures objectAtIndex: i] key] userID], [(GPGSignature *)[signatures objectAtIndex: i] fingerprint]];
                    break;
                case GPGSignatureStatusGoodButExpired:
                    [statuses appendFormat: NSLocalizedString(FTGoodButExpiredSigStatus, nil), [[signatures objectAtIndex: i] creationDate], GPGValidityDescription([[signatures objectAtIndex: i] validity]), [[(GPGSignature *)[signatures objectAtIndex: i] key] userID], [(GPGSignature *)[signatures objectAtIndex: i] fingerprint]];
                    break;
                case GPGSignatureStatusGoodButKeyExpired:
                    [statuses appendFormat: NSLocalizedString(FTGoodButKeyExpiredSigStatus, nil), [[signatures objectAtIndex: i] creationDate], GPGValidityDescription([[signatures objectAtIndex: i] validity]), [[(GPGSignature *)[signatures objectAtIndex: i] key] userID], [(GPGSignature *)[signatures objectAtIndex: i] fingerprint]];
                    break;
                case GPGSignatureStatusNoKey:
                    [statuses appendFormat: NSLocalizedString(FTNoKeySigStatus, nil), [[signatures objectAtIndex: i] fingerprint]];
                    break;
                case GPGSignatureStatusNoSignature:
                    [statuses appendFormat: NSLocalizedString(FTNoSignatureSigStatus, nil)];
                    break;
                default:
                    [statuses appendFormat: NSLocalizedString(FTErrorSigStatus, nil)];
                    break;
            }
        }

        NSRunInformationalAlertPanelRelativeToWindow(NSLocalizedString(FTMultipleSignatureStatuses, nil), statuses, nil, nil, nil, [self window]);
    }
}

- (NSData *)encryptAndSign
{
    GPGRecipients *recipients = nil;
    NSEnumerator *signers = nil;
    NSData *returned_data = nil;
    GPGKey *signer = nil;

    recipients = [defaults boolForKey: @"select_single_recipient"] ? [self getRecipient] : [self getRecipients];

    if ([recipients count])	{
        signers = [defaults boolForKey: @"select_single_signer"] ? [self getSigner] : [self getSigners];

        if (signers)	{
            NS_DURING
                GPGContext *context = [[[GPGContext alloc] init] autorelease];

                [context setUsesArmor: [ckbox_armored state] ? YES : NO];
                [context setPassphraseDelegate: self];

                while (signer = [signers nextObject])
                    [context addSignerKey: signer];

                returned_data = [[context encryptedSignedData: gpgData
                                                forRecipients: recipients
                                        allRecipientsAreValid: nil]
                    data];

            NS_HANDLER
                [self handleException: localException];
            NS_ENDHANDLER
        }
    }

    return returned_data;
}

- (NSData *)encrypt
{
    GPGRecipients *recipients = nil;
    NSData *returned_data = nil;

    recipients = [defaults boolForKey: @"select_single_recipient"] ? [self getRecipient] : [self getRecipients];

    if ([recipients count])	{
        NS_DURING
            GPGContext *context = [[[GPGContext alloc] init] autorelease];

            [context setUsesArmor: [ckbox_armored state] ? YES : NO];

            returned_data = [[context encryptedData:gpgData forRecipients:recipients allRecipientsAreValid:nil]
                data];

        NS_HANDLER
            [self handleException: localException];
        NS_ENDHANDLER
    }

    return returned_data;
}

- (NSData *)sign
{
    GPGKey *signer = nil;
    NSData *returned_data = nil;
    NSEnumerator *signers = nil;

    signers = [defaults boolForKey: @"select_single_signer"] ? [self getSigner] : [self getSigners];

    if (signers)	{
        NS_DURING
            GPGContext *context = [[[GPGContext alloc] init] autorelease];

            [context setUsesArmor: [ckbox_armored state] ? YES : NO];
            [context setPassphraseDelegate: self];

            while (signer = [signers nextObject])
                [context addSignerKey: signer];

            returned_data = [[context signedData:gpgData signatureMode: GPGSignatureModeNormal]
                data];
            //[context wait: YES];

        NS_HANDLER
            [self handleException: localException];
        NS_ENDHANDLER
    }

    return returned_data;
}

- (NSData *)signDetached
{
    GPGKey *signer = nil;
    NSData *returned_data = nil;
    NSEnumerator *signers = nil;

    signers = [defaults boolForKey: @"select_single_signer"] ? [self getSigner] : [self getSigners];
    //NSLog("%@", signer);

    if (signers)	{
        NS_DURING
            GPGContext *context = [[[GPGContext alloc] init] autorelease];

            [context setUsesArmor: [ckbox_armored state] ? YES : NO];
            [context setPassphraseDelegate: self];

            while (signer = [signers nextObject])
                [context addSignerKey: signer];

            returned_data = [[context signedData: gpgData signatureMode: GPGSignatureModeDetach]
                data];
            //[context wait: YES];

        NS_HANDLER
            [self handleException: localException];
        NS_ENDHANDLER
    }

    return returned_data;
}

- (NSData *)clearsign
{
    GPGKey *signer = nil;
    NSData *returned_data = nil;
    NSEnumerator *signers = nil;

    signers = [defaults boolForKey: @"select_single_signer"] ? [self getSigner] : [self getSigners];

    if (signers)	{
        NS_DURING
            GPGContext *context = [[[GPGContext alloc] init] autorelease];

            [context setUsesArmor: [ckbox_armored state] ? YES : NO];
            [context setPassphraseDelegate: self];

            while (signer = [signers nextObject])
                [context addSignerKey: signer];

            returned_data = [[context signedData:gpgData signatureMode: GPGSignatureModeClear]
                data];
            //[context wait: YES];

        NS_HANDLER
            [self handleException: localException];
        NS_ENDHANDLER
    }

    return returned_data;
}

- (NSData *)symmetricallyEncrypt
{
    NSData *returned_data = nil;
    GPGContext *context = nil;

    NS_DURING
        context = [[GPGContext alloc] init];

        [context setUsesArmor: [ckbox_armored state] ? YES : NO];
        [context setPassphraseDelegate: self];

        returned_data = [[context encryptedData: gpgData] data];
    NS_HANDLER
        [self handleException: localException];
    NS_ENDHANDLER

    [context release];

    return returned_data;
}


- (NSData *)decryptAndVerify
{
    NSData *returned_data = nil;
    GPGSignatureStatus sig_status;

    NS_DURING
        GPGContext *context = [[[GPGContext alloc] init] autorelease];
        //GPGKey *signee;

        [context setPassphraseDelegate: self];

        returned_data = [[context decryptedData: gpgData signatureStatus: &sig_status] data];

        [self showVerificationStatus: [context signatures]];
    NS_HANDLER
        [self handleException: localException];
    NS_ENDHANDLER

    return returned_data;
}

- (NSData *)decrypt
{
    NSData *returned_data = nil;

    NS_DURING
        GPGContext *context = [[[GPGContext alloc] init] autorelease];

        [context setPassphraseDelegate: self];

        returned_data = [[context decryptedData: gpgData] data];
    NS_HANDLER
        [self handleException: localException];
    NS_ENDHANDLER

    return returned_data;
}

- (NSData *)verify
{
    NS_DURING
        GPGContext *context = [[[GPGContext alloc] init] autorelease];

        [context setPassphraseDelegate: self];

        [context verifySignedData: gpgData];

        [self showVerificationStatus: [context signatures]];
    NS_HANDLER
        [self handleException: localException];
    NS_ENDHANDLER

    return nil;
}

- (NSData *)verifyDetached
{
    GPGSignatureStatus sig_status;

    NS_DURING
        GPGContext *context = [[[GPGContext alloc] init] autorelease];
        GPGData *orig_data;

        orig_data = [[[GPGData alloc] initWithData: [self dataForDetachedSignature]] autorelease];

        [context setPassphraseDelegate: self];

        sig_status = [context verifySignatureData: gpgData againstData: orig_data];

        [self showVerificationStatus: [context signatures]];
    NS_HANDLER
        [self handleException: localException];
    NS_ENDHANDLER

    return nil;
}

- (BOOL) shouldDisplayKey: (GPGKey *)key contextInfo: (id)info
{
    if ([info isEqualTo: @"recipients"])
    {
        if ([key validity] >= GPGValidityMarginal && [key canEncrypt])
            return YES;
    }
    else if ([info isEqualTo: @"signers"])
    {
        if ([[key publicKey] canSign])
            return YES;
    }

    return NO;
}

@end