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
	
	int x_size;
	int y_size;
	
	bool xAxis;
	bool yAxis;
	bool zAxis;
	
	Matrix * m_draw;

    NSTimer * timer;
    NSTimeInterval lastTime;
}

// Data
- (BOOL)readPoints:(NSString *)fileName;
- (BOOL)readLines:(NSString *)fileName;

// Drawing
- (void)drawRect:(NSRect)rect;
- (void)rotate:(bool)x y:(bool)y z:(bool)z angle:(double)r;

// Custom methods for actions this view implements
- (IBAction)translate_X:(id)sender;
- (IBAction)translate_Y:(id)sender;
- (IBAction)zoom:(id)sender;
- (IBAction)rotate_X:(id)sender;
- (IBAction)rotate_Y:(id)sender;
- (IBAction)rotate_Z:(id)sender;
- (IBAction)sheer_X:(id)sender;
- (IBAction)anim:(id)sender;
- (IBAction)setXaxis:(id)sender;
- (IBAction)setYaxis:(id)sender;
- (IBAction)setZaxis:(id)sender;
- (IBAction)reset:(id)sender;

// Timers
- (void)anim_go:(NSTimer *)aTimer;

@end
