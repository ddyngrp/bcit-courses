//
//  GPGPassphrasePanelController.m
//  GPGAppKit
//
//  Copyright (C) 2001-2003 Mac GPG Project.
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

#import "GPGPassphrasePanelController.h"
#import <MacGPGME/MacGPGME.h>

static GPGPassphrasePanelController * sharedGPGPassphrasePanelController = nil;

@implementation GPGPassphrasePanelController
/*"
GPGPassphrasePanel provides an interface for passphrase capture similar to
that provided by NSSavePanel/NSOpenPanel.
"*/

+ (id) sharedPassphrasePanelController
{    
    if (sharedGPGPassphrasePanelController == nil)
        sharedGPGPassphrasePanelController =
            [[[GPGPassphrasePanelController alloc] initWithWindowNibName: @"GPGPassphrasePanel"] autorelease];
    return sharedGPGPassphrasePanelController;
}

+ (id) passphrasePanelController
{
    GPGPassphrasePanelController *tmp = [[GPGPassphrasePanelController alloc] initWithWindowNibName: @"GPGPassphrasePanel"];
    [tmp resetToDefaults];
    return [tmp autorelease];
}

- (void) resetToDefaults {
    [self setTitle:[[NSBundle bundleForClass:[self class]] localizedStringForKey:GPGAppKitPassphrasePanelTitle
                                                                            value:@"Arse"
                                                                            table:nil]];
    [passphraseTextField setStringValue:@""];
    [okButton setEnabled:NO];
    okPressed = NO;
}

- (void) setTitle: (NSString *) title {
    double	newWidth, oldWidth;
    NSRect	frame;
    
    [[self window] setTitle:title];
    [titleTextField setStringValue:title];
    
    // Resize title textfield and passphrase entry field to fit.
    oldWidth = [titleTextField frame].size.width;
    [titleTextField sizeToFit];
    newWidth = [titleTextField frame].size.width;
    frame = [passphraseTextField frame];
    frame.origin.x += newWidth - oldWidth;
    frame.size.width -= newWidth - oldWidth;
    [passphraseTextField setFrame:frame];
}

- (NSString *) title {
    return [titleTextField stringValue];
}

- (void) setPrompt: (NSString *) prompt {
    [promptTextField setStringValue:prompt];
}
- (NSString *) prompt {
    return [promptTextField stringValue];
}

- (void) beginSheetWithPrompt: (NSString *) aString
               modalForWindow: (NSWindow *) parentWindow
                modalDelegate: (id) delegate
               didEndSelector: (SEL) endSelector
                  contextInfo: (id) info
{
    [self resetToDefaults];
    [self setPrompt:aString];
    
    [NSApp beginSheet: [self window]
       modalForWindow: parentWindow
        modalDelegate: delegate
       didEndSelector: endSelector
          contextInfo: info];
}
- (BOOL) runModalWithPrompt: (NSString *) aString {
    [self resetToDefaults];
    [self setPrompt:aString];
    
    [NSApp runModalForWindow: [self window]];
    
    if (okPressed)
        return NSOKButton;
    else
        return NSCancelButton;
}

//deprecated fucntion, use at own risk
//I needed this, but you should try to do it a better way.
- (BOOL) runModalWithPrompt: (NSString *) aString relativeToWindow: (NSWindow *) parentWindow
{    
    [self resetToDefaults];
    [self setPrompt:aString];

    [NSApp runModalForWindow: [self window] relativeToWindow: parentWindow];
    
    if (okPressed)
        return NSOKButton;
    else
        return NSCancelButton;
}

- (void)windowDidStartSheet:(NSNotification *)notification
{
    sheetOpen = YES;
}

- (void)windowDidEndSheet:(NSNotification *)notification
{
    sheetOpen = NO;
}

- (NSString *) passphrase {
    if (okPressed)
        return [[passphraseTextField stringValue] copy];
    else
        return nil;
}

- (void) cancel: (id) sender {
    [passphraseTextField setStringValue:@""];
    
    if ([[self window] isSheet])
        [NSApp endSheet: [self window]];
    else
        [NSApp stopModal];
    
    okPressed = NO;
    [[self window] orderOut:nil];
}

- (void) ok: (id) sender {
    if ([[self window] isSheet])
        [NSApp endSheet: [self window]];
    else
        [NSApp stopModal];

    okPressed = YES;
    [[self window] orderOut:nil];
}

- (void)controlTextDidChange:(NSNotification *)aNotification
{
    BOOL		passphraseEmpty;
    NSTextView	*text = [passphraseTextField currentEditor];
    if (text)
        passphraseEmpty = [[text textStorage] length] == 0;
    else
        passphraseEmpty = [[passphraseTextField stringValue] length] == 0;
    
    // Disable the OK button if there is no passphrase specified
    [okButton setEnabled: !passphraseEmpty];
}


@end
