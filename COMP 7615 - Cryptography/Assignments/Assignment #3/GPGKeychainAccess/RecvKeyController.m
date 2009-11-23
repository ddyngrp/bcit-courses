//  RecvKeyController.m
//  GPG Keychain Access
//
//  Created by redbird one day
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

#import "RecvKeyController.h"

@implementation RecvKeyController

- (void)awakeFromNib
{
    [[self window] setExcludedFromWindowsMenu:YES];
    [[self window] setMenu:nil];
    [[self window] center];
}

- (IBAction)recvKeyFromServer:(id)sender
{
    NSTask *edit_task, *activate_task;
    NSMutableArray *args;
    NSMutableString *as_script;

    //task to activate Terminal
    args = [NSMutableArray array];
    [args addObject: @"-e"];
    [args addObject: @"tell application \"Terminal.app\" to activate"];

    activate_task = [[NSTask alloc] init];
    [activate_task setLaunchPath: @"/usr/bin/osascript"];
    [activate_task setArguments: args];

    [activate_task launch];
    [activate_task release];

    //get key
    as_script = [NSMutableString stringWithString: @"tell application \"Terminal.app\" to do script with command \""];
    [as_script appendString: @"gpg --recv-key "];
    [as_script appendString: [key_id_field stringValue]];
    [as_script appendString: @"\""];

    [args removeLastObject];
    [args addObject: as_script];
    
    edit_task = [[NSTask alloc] init];
    [edit_task setLaunchPath: @"/usr/bin/osascript"];
    [edit_task setArguments: args];

    [edit_task launch];
    [edit_task waitUntilExit];  //lets the user know that their waiting for something
    [edit_task release];

    [NSApp stopModal];
    [[self window] close];
}

- (IBAction) cancel: (id)sender
{
    [NSApp stopModal];
    [[self window] close];
}

@end
