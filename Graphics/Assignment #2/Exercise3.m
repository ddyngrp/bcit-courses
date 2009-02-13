//
//  Exercise3.m
//  Assignment #2
//
//  Created by Steffen L. Norgren on 14/01/09.
//  Copyright 2009 Esurient Systems Inc.. All rights reserved.
//

#import "Exercise3.h"


@implementation Exercise3

- (void)drawRect:(NSRect)rect {
	// Set the window's title (fix this, it does it after clicking)
	[[self window] setTitle:@"Exercise #3"];
	
	// Set height/width variables
	int h = rect.size.height;
	int w = rect.size.width;
	
	// Set geometry variables
	int ls = 30;		// the space between each line
	int lw = ls / 5;	// the width of each line
	int d = (int)round(sqrt((lw * lw) + (lw * lw))); // the diameter of each circle
	
	
	// Set custom colours we'll be using
	NSColor *colourGrey = [NSColor colorWithCalibratedRed:0.6 green:0.6 blue:0.6 alpha:1.0];
	
	// Create a black background for the window
	[[NSColor blackColor] set];
	[NSBezierPath fillRect:[self bounds]];	
	
	// Create the grid of grey lines
	[colourGrey set];
	for (int ULx = ls / 2; ULx < w; ULx += ls) {
		[[NSBezierPath bezierPathWithRect:NSMakeRect(ULx, 0, lw, h)] fill];
	}
	for (int ULy = ls / 2; ULy < h; ULy += ls) {
		[[NSBezierPath bezierPathWithRect:NSMakeRect(0, ULy, w, lw)] fill];
	}
	
	// Draw the circles at each intersection point
	[[NSColor whiteColor] set];
	for (int ULx = ls / 2; ULx < w; ULx += ls) {
		for (int ULy = ls / 2; ULy < h; ULy += ls) {
			[[NSBezierPath bezierPathWithOvalInRect:NSMakeRect(ULx - ((d - lw) / 2), ULy - ((d - lw) / 2),
															   d, d)] fill];			
		}
	}
	// Redraw the window in the event of a resize event
    if ([self inLiveResize])
    {
        NSRect rects[4];
        int count;
        [self getRectsExposedDuringLiveResize:rects count:&count];
        while (count-- > 0)
        {
            [self setNeedsDisplayInRect:rects[count]];
        }
    }
    else
    {
        [self setNeedsDisplay:YES];
    }	
}

@end
