//
//  Exercise1.m
//  Assignment #2
//
//  Created by Steffen L. Norgren on 14/01/09.
//  Copyright 2009 Esurient Systems Inc.. All rights reserved.
//

#import "Exercise1.h"


@implementation Exercise1

- (void)drawRect:(NSRect)rect {
	int s, Mx, My;

	// Set the window's title (fix this, it does it after clicking)
	[[self window] setTitle:@"Exercise #1"];
	
	// Set minimum size
	if (rect.size.width > rect.size.height) {
		s = rect.size.height;
	}
	else {
		s = rect.size.width;
	}
	
	// Set the centre co-ordinates
	Mx = (rect.size.width - 1) / 2;
	My = (rect.size.height - 1) / 2;
	
	// Set custom colours we'll be using
	NSColor *colourGreen = [NSColor colorWithCalibratedRed:0.0 green:0.7529 blue:0.0 alpha:1.0];

	// Create a black background
	NSRect bounds = [self bounds];
	[[NSColor blackColor] set];
	[NSBezierPath fillRect:bounds];	

	// Draw Large Circle 1
	[[NSColor blueColor] set];
	[[NSBezierPath bezierPathWithOvalInRect:NSMakeRect(Mx - ((5 * s)/12), My + (s/12), s/3, s/3)] fill];
	
	// Draw Small Circle 1
	[colourGreen set];
	[[NSBezierPath bezierPathWithOvalInRect:NSMakeRect(Mx - (s/3), My + (s/6), s/6, s/6)] fill];

	// Draw Large Circle 2
	[[NSColor yellowColor] set];
	[[NSBezierPath bezierPathWithOvalInRect:NSMakeRect(Mx + (s/12), My + (s/12), s/3, s/3)] fill];
	
	// Draw Small Circle 2
	[colourGreen set];
	[[NSBezierPath bezierPathWithOvalInRect:NSMakeRect(Mx + (s/6), My + (s/6), s/6, s/6)] fill];
	
	// Draw Large Circle 3
	[[NSColor blueColor] set];
	[[NSBezierPath bezierPathWithOvalInRect:NSMakeRect(Mx - ((5 * s)/12), My - ((5 * s)/12), s/3, s/3)] fill];

	// Draw Small Circle 3
	[[NSColor redColor] set];
	[[NSBezierPath bezierPathWithOvalInRect:NSMakeRect(Mx - (s/3), My - (s/3), s/6, s/6)] fill];
	
	// Draw Large Circle 4
	[[NSColor yellowColor] set];
	[[NSBezierPath bezierPathWithOvalInRect:NSMakeRect(Mx + (s/12), My - ((5 * s)/12), s/3, s/3)] fill];
	
	// Draw Small Circle 4
	[[NSColor redColor] set];
	[[NSBezierPath bezierPathWithOvalInRect:NSMakeRect(Mx + (s/6), My - (s/3), s/6, s/6)] fill];

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
