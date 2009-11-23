//
//  GPGDocument_Utility.m
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
#import "NSString_GPGFTExtensions.h"
#import <unistd.h>

@implementation GPGDocument (Utility)

- (NSWindow *)window
{
    return [[[self windowControllers] objectAtIndex: 0] window];
}

- (void)handleException: (NSException *) exception
{
    if ([exception isEqualTo: [NSException exceptionWithGPGError: GPGErrorCanceled userInfo: nil]])
        return;
    else
    {
        NSBeginAlertSheet(NSLocalizedString(FTErrorTitle, nil), nil, nil, nil, [self window], nil, nil, nil,
                          nil, NSLocalizedString(FTErrorMessage, nil), exception);
    }
}

- (void)openFileWithFilename: (NSString *)filename
{
    [[NSWorkspace sharedWorkspace] openFile: filename];
}

- (void)showInFinder: (NSString *)filename
{
    NSTask *open_file_task = [[NSTask alloc] init];
    NSMutableArray *args = [NSMutableArray array];
    NSMutableString *script = [NSMutableString string];

    [script appendString: @"tell application \"Finder\" to (reveal file \""];
    [script appendString: [filename unixAsMacPath]];
    [script appendString: @"\") activate"];

    [args addObject: @"-e"];
    [args addObject: script];

    [open_file_task setLaunchPath: @"/usr/bin/osascript"];
    [open_file_task setArguments: args];
    [open_file_task launch];

    [open_file_task waitUntilExit]; //good since this can take several seconds

    [open_file_task release];
}

- (void)deleteOriginalFile
{
    NSTask *rmFileTask;
    NSMutableArray *args;

    if ([defaults boolForKey: @"warn_before_delete"])
    {
        if (1 != NSRunAlertPanelRelativeToWindow(NSLocalizedString(FTWarningTitle, nil),
                                                 NSLocalizedString(FTSecureDeleteWarningMessage, nil),
                                                 NSLocalizedString(FTOkay, nil), NSLocalizedString(FTCancel, nil),
                                                 nil, [self window]))
            return;
    }

    if ([[NSFileManager defaultManager] isDeletableFileAtPath: [self fileName]])
    {
        rmFileTask = [[NSTask alloc] init];
        args = [[NSMutableArray alloc] init];
        [args addObject: @"-fP"];
        [args addObject: [self fileName]];
    
        [rmFileTask setLaunchPath: @"/bin/rm"];
        [rmFileTask setArguments: args];
        [rmFileTask launch];
    
        [rmFileTask waitUntilExit];
    
        [rmFileTask release];
        [args release];

        NSBeginAlertSheet(NSLocalizedString(FTSecureDeleteSucceededTitle, nil), NSLocalizedString(FTClose, nil),
                          nil, nil, [self window], self, @selector(sheetDidEnd:returnCode:contextInfo:), nil,
                          nil, NSLocalizedString(FTSecureDeleteSucceededMessage, nil));
    }
    else
    {
        NSBeginAlertSheet(NSLocalizedString(FTSecureDeleteFailedTitle, nil), NSLocalizedString(FTOkay, nil),
                          nil, nil, [self window], nil, nil, nil, nil,
                          NSLocalizedString(FTSecureDeleteFailedMessage, nil));
    }
}

- (void)sheetDidEnd:(NSWindow *)sheet returnCode:(int)returnCode contextInfo:(void *)contextInfo
{
    [self close];
}

@end