//
//  GPGDocument.m
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

#import "GPGDocument.h"
#import "LocalizableStrings.h"

@implementation GPGDocument

- (id)init
{
    NSMutableArray *objs, *keys;
    
    [super init];

    defaults = [[NSUserDefaults standardUserDefaults] retain];
    
    gpgData = nil;

    //needed later on for writing files
    objs = [NSMutableArray array];
    keys = [NSMutableArray array];
    [keys addObject: @"Encrypted & Signed file"];
    [objs addObject: @"gpg"];
    [keys addObject: @"Encrypted file"];
    [objs addObject: @"gpge"];
    [keys addObject: @"Signed file"];
    [objs addObject: @"gpgs"];
    [keys addObject: @"Detached signature"];
    [objs addObject: @"sig"];
    [keys addObject: @"Clearsigned file"];
    [objs addObject: @"asc"];
    [keys addObject: @"Symmetrically Encrypted file"];
    [objs addObject: @"gpgc"];
    [keys addObject: @"Data"];
    [objs addObject: @""];
    types = [[NSDictionary alloc] initWithObjects: objs forKeys: keys];

    return self;
}

- (void)dealloc
{
    if (gpgData)
        [gpgData release];
    [types release];
    [defaults release];

    [super dealloc];
}

- (BOOL)writeFileWithData: (NSData *)data ofType: (NSString *)type
{
    NS_DURING
        NSSavePanel	*sp;
        NSMutableString *new_filename;
        char *old_filename;
        int of_len, i, suffix_start;

        sp = [NSSavePanel savePanel];

        [sp setTreatsFilePackagesAsDirectories: YES];
        [sp setRequiredFileType: [types objectForKey: type]];

        if ([type isEqualTo: @"Data"])	{
            old_filename = [[self displayName] cString];
            of_len = [[self displayName] length];
            //remove the suffix
            for (i = of_len - 1; i >= 0; i--)	{
                if (*(old_filename + i) == '.')	{
                    suffix_start = i;
                    i = -1;
                }
            }
            new_filename = [NSString stringWithCString: old_filename length: suffix_start];
        }
        else	{
            new_filename = [NSMutableString stringWithString: [self displayName]];
            [new_filename appendString: @"."];
            [new_filename appendString: [types objectForKey: type]];
        }

        if([sp runModalForDirectory: nil file: new_filename relativeToWindow: [self window]] == NSOKButton){
            [data writeToFile:[sp filename] atomically:NO];
            [outFilename release];
            outFilename = [[sp filename] copy];
            NS_VALUERETURN(YES, BOOL);
        }
        else
            NS_VALUERETURN(NO, BOOL);
    NS_HANDLER
        [self handleException: localException];
    NS_ENDHANDLER

    return NO;
}

- (NSData *)dataForDetachedSignature
{
    NSData *orig_data = nil;

    NS_DURING
        //get the data from the original file
        orig_data = [NSData dataWithContentsOfFile:
            [[self fileName] substringToIndex: [[self fileName] length] - 4]]; //strip the .sig extension
        //NSLog([[self fileName] substringToIndex: [[self fileName] length] - 4]);
        //NSLog(@"%@", orig_data);
    NS_HANDLER
        [self handleException: localException];
    NS_ENDHANDLER

    if (orig_data == nil)	{
        NSOpenPanel *op;
        op = [NSOpenPanel openPanel];

        [op setTreatsFilePackagesAsDirectories: YES];
        [op setAllowsMultipleSelection: NO];
        [op setTitle: NSLocalizedString(FTVerifyFileFindTitle, nil)];
        [op setPrompt: NSLocalizedString(FTVerifyFileFindPrompt, nil)];

        if ([op runModalForDirectory: nil file: nil types: nil relativeToWindow: [self window]] == NSOKButton)	{
            orig_data = [NSData dataWithContentsOfFile: [op filename]];
        }
    }

    return orig_data;
}

/*====================
 NSDocument methods
====================*/

- (NSString *)windowNibName
{
    // Override returning the nib file name of the document
    // If you need to use a subclass of NSWindowController or if your document supports multiple NSWindowControllers, you should remove this method and override -makeWindowControllers instead.
    return @"GPGDocument";
}

- (void)windowControllerDidLoadNib:(NSWindowController *) aController
{
    [super windowControllerDidLoadNib:aController];
    [pathToFile setStringValue: [self fileName]];
    //NSLog([self fileType]);
    if ([[self fileType] isEqualTo: @"Encrypted & Signed file"])
        [actionList selectItemAtIndex: [defaults boolForKey:
            @"default_decrypt_and_verify"] ? GPGFTDecryptAndVerify : GPGFTDecrypt ];
    else if ([[self fileType] isEqualTo: @"Encrypted file"])
        [actionList selectItemAtIndex: GPGFTDecrypt];
    else if ([[self fileType] isEqualTo: @"Signed file"])
        [actionList selectItemAtIndex: GPGFTVerify];
    else if ([[self fileType] isEqualTo: @"Detached signature"])
        [actionList selectItemAtIndex: GPGFTVerifyDetached];
    else if ([[self fileType] isEqualTo: @"Clearsigned file"])
        [actionList selectItemAtIndex: GPGFTVerify];
    else if ([[self fileType] isEqualTo: @"Symmetrically Encrypted file"])
        [actionList selectItemAtIndex: GPGFTDecrypt];
    else
        [actionList selectItemAtIndex: [defaults integerForKey: @"user_default_action"]];
    
    [ckbox_armored setState: [defaults boolForKey: @"default_armored"] ? NSOnState : NSOffState];
    [ckbox_showAfter setState: [defaults boolForKey: @"default_show_after"] ? NSOnState : NSOffState];
    if (!([defaults boolForKey: @"default_open_unless_ciphered"] && [[self fileType] isNotEqualTo: @"Data"]))
        [ckbox_openAfter setState: [defaults boolForKey: @"default_open_after"] ? NSOnState : NSOffState];
    [ckbox_deleteOriginal setState: [defaults boolForKey: @"default_delete_original"] ? NSOnState : NSOffState];

    [self actionSelectionChanged: self];
}

- (NSData *)dataRepresentationOfType:(NSString *)aType
{
    // nothing happens here
    // since you can't change a file to need to save it
    // just write out a new file
    // but it has to be here, required by NSDocument
    return nil;
}

- (BOOL)loadDataRepresentation:(NSData *)data ofType:(NSString *)filetype
{
    NS_DURING
            gpgData = [[GPGData alloc] initWithData: data];
            NS_VALUERETURN(YES, BOOL);
    NS_HANDLER
        return NO;
    NS_ENDHANDLER
}

@end