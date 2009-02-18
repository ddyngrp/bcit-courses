//
//  Transform.m
//  Assignment #5
//
//  Created by Steffen L. Norgren on 13/02/09.
//  Copyright 2009 Esurient Systems Inc.. All rights reserved.
//

#import "Transform.h"
#import "Controller.h"


@implementation Transform

- (id)initWithFrame:(NSRect)frame {
	[super initWithFrame:frame];
	
	return self;
}

- (void)drawRect:(NSRect)rect {
	NSBezierPath * aPath = [NSBezierPath bezierPath];
	Matrix * m_lines, * m_points;
	int p1, p2;
	float x1, y1, x2, y2;
	
	m_lines = [Controller m_lines];
	m_points = [Controller m_points];
	
	[NSBezierPath setDefaultLineWidth:1.0];
	
	for (int i = 0; i < [m_lines maxY]; i++) {
		p1 = [[m_lines atX:0 atY:i] intValue];
		p2 = [[m_lines atX:1 atY:i] intValue];
		
		x1 = [[m_points atX:0 atY:p1] floatValue];
		y1 = [[m_points atX:1 atY:p1] floatValue];
		x2 = [[m_points atX:0 atY:p2] floatValue];
		y2 = [[m_points atX:1 atY:p2] floatValue];
		
		// TODO: Image needs to be 1/2 vertical height and in the centre
		// this should be done via a translation I would think.
		[aPath moveToPoint:NSMakePoint(x1 * 20 + 125, y1 * 20 + 25)];
		[aPath lineToPoint:NSMakePoint(x2 * 20 + 125, y2 * 20 + 25)];
	}
	[aPath stroke]; // Draw the result
	
	// Reduce detail while being resized
    if ([self inLiveResize])
    {
        NSRect rects[4];
        int count;
		[NSBezierPath setDefaultFlatness:20.0];
        [self getRectsExposedDuringLiveResize:rects count:&count];
        while (count-- > 0)
        {
            [self setNeedsDisplayInRect:rects[count]];
        }
    }
    else
    {
		[NSBezierPath setDefaultFlatness:0.6];
        [self setNeedsDisplay:YES];
    }
}

- (void)dealloc {
	[super dealloc];
}

@end
