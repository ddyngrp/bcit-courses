//
//  Transform.h
//  Assignment #5
//
//  Created by Steffen L. Norgren on 13/02/09.
//  Copyright 2009 Esurient Systems Inc.. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <Foundation/NSArray.h>
#import "Matrix.h"

@interface Transform : NSView {
	Matrix * m_transform;
	Matrix * m_rotate;
	Matrix * m_sheer;
	Matrix * m_scale;
	
	Matrix * m_product;
	Matrix * m_points;
	Matrix * m_lines;
}

// Data
- (BOOL)readPoints:(NSString *)fileName;
- (BOOL)readLines:(NSString *)fileName;

// Drawing
- (void)drawRect:(NSRect)rect;

// Custom methods for actions this view implements
- (IBAction)translate_X:(id)sender;
//- (IBAction)translate_Y:(id)sender;
//- (IBAction)zoom:(id)sender;
//- (IBAction)rotate_X:(id)sender;
//- (IBAction)rotate_Y:(id)sender;
//- (IBAction)rotate_Z:(id)sender;
//- (IBAction)sheer_X:(id)sender;
//- (IBAction)rotation_animation:(id)sender;
//- (IBAction)reset:(id)sender;

@end
