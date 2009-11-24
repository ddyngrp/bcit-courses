//
//  GPGFTController.m
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

#import "GPGFTController.h"
#import "GPGDocument.h"

@implementation GPGFTController

- (id)init
{
    [super init];

    return self;
}

- (void)dealloc
{
    [super dealloc];
}

- (IBAction) showPrefs: (id)sender
{
    if (prefController == nil)
    {
        prefController = [[GPGPrefController alloc] initWithWindowNibName:@"Preferences"];
        if (prefController == nil)
        {
            NSLog(@"Failed to load Preferences.nib");
            NSBeep();
            return;
        }
    }

    [[prefController window] makeKeyAndOrderFront:nil];
}

- (IBAction)showGPGPrefs: (id)sender
{
    [[NSWorkspace sharedWorkspace] openFile: @"/Library/PreferencePanes/GnuPG.prefPane"];
}

/*====================
 Application delegate
====================*/

- (BOOL)applicationShouldOpenUntitledFile:(NSApplication *)sender
{
    //we only handle files with data in them
    //and create new ones based on them
    return NO;
}

/*====================
 Application notifications
====================*/

- (void)applicationDidFinishLaunching: (NSNotification *)notification
{
    NSDocumentController *dc = [NSDocumentController sharedDocumentController];
    
    if ([[NSUserDefaults standardUserDefaults] integerForKey: @"activation_behavior"] == GPGFT_ABOpenLaunchOnly
        &&
        [[dc documents] count] == 0)
    {
        [dc openDocument: self];
    }
}

- (void)applicationDidBecomeActive: (NSNotification *)notification
{
    NSDocumentController *dc = [NSDocumentController sharedDocumentController];
    
    if ([[NSUserDefaults standardUserDefaults] integerForKey: @"activation_behavior"] == GPGFT_ABOpen
        &&
        [[dc documents] count] == 0)
    {
        [dc openDocument: self];
    }
}
    
@end
