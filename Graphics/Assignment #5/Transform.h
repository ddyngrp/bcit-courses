//
//  Transform.h
//  Assignment #5
//
//  Created by Steffen L. Norgren on 13/02/09.
//  Copyright 2009 Esurient Systems Inc.. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>

@interface Transform : NSView {
	NSMutableArray * points;
	NSMutableArray * lines;
}

// Drawing
- (void)drawRect:(NSRect)rect;

// Data Methods
- (NSMutableArray *)points;
- (NSMutableArray *)lines;
- (void)setPoints:(NSMutableArray *)newPoints;
- (void)setLines:(NSMutableArray *)newLines;
- (BOOL)readPoints:(NSString *)fileName;
- (BOOL)readLines:(NSString *)fileName;

// Event handling
//- (void)mouseUp:(NSEvent *)event;

// Custom methods for actions this view implements
//- (IBAction)translate_X:(id)sender;
//- (IBAction)translate_Y:(id)sender;
//- (IBAction)zoom:(id)sender;
//- (IBAction)rotate_X:(id)sender;
//- (IBAction)rotate_Y:(id)sender;
//- (IBAction)rotate_Z:(id)sender;
//- (IBAction)sheer_X:(id)sender;
//- (IBAction)rotation_animation:(id)sender;
//- (IBAction)reset:(id)sender;

@end
