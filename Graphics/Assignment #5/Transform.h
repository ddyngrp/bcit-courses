//
//  Transform.h
//  Assignment #5
//
//  Created by Steffen L. Norgren on 13/02/09.
//  Copyright 2009 Esurient Systems Inc.. All rights reserved.
//

#import <Cocoa/Cocoa.h>


@interface Transform : NSView {
}

// Drawing
- (void)drawRect:(NSRect)rect;

// Event handling
- (void)mouseUp:(NSEvent *)event;

// Custom methods for actions this view implements
- (IBAction)translate_X:(id)sender;
- (IBAction)translate_Y:(id)sender;
- (IBAction)zoom:(id)sender;
- (IBAction)rotate_X:(id)sender;
- (IBAction)rotate_Y:(id)sender;
- (IBAction)rotate_Z:(id)sender;
- (IBAction)sheer_X:(id)sender;
- (IBAction)rotation_animation:(id)sender;
- (IBAction)reset:(id)sender;

// Menu Actions
- (IBAction)file_new:(id)sender;
- (IBAction)file_open:(id)sender; // Make this work first
- (IBAction)file_save:(id)sender;
- (IBAction)file_saveAs:(id)sender;
- (IBAction)file_revert:(id)sender;

@end
