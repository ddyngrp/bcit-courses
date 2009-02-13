//
//  Exercise2.m
//  Assignment #2
//
//  Created by Steffen L. Norgren on 14/01/09.
//  Copyright 2009 Esurient Systems Inc.. All rights reserved.
//

#import "Exercise2.h"


@implementation Exercise2

- (void)drawRect:(NSRect)rect {
	int s, g, h, w, ULx, ULy;
	
	// Set the window's title (fix this, it does it after clicking)
	[[self window] setTitle:@"Exercise #2"];
	
	// Set our other variables
	h = rect.size.height;
	w = rect.size.width;
	s = 10;
	g = 4;

	// Set custom colours we'll be using
	NSColor *colourLightGreen = [NSColor colorWithCalibratedRed:0.745098 green:1.0 blue:0.0 alpha:1.0];
	
	// Create a white background for the window
	[[NSColor whiteColor] set];
	[NSBezierPath fillRect:[self bounds]];	

	// Create a black background on the left half of the window
	[[NSColor blackColor] set];
	[[NSBezierPath bezierPathWithRect:NSMakeRect(0, 0, w / 2, h)] fill];
	
	// Draw the boxes
	if (h > (3 * s + 2 * g) && w > (3 * s + 2 * g)) {
		for (ULy = h - (s + g); ULy > (2 * s + g); ULy -= s + g) {
			for (ULx = w / 2; ULx < w - (2 * s + g); ULx += s + g) {
				[colourLightGreen set];
				[[NSBezierPath bezierPathWithRect:NSMakeRect(ULx, ULy, s, -s)] fill];
				[[NSBezierPath bezierPathWithRect:NSMakeRect(w - ULx, ULy, -s, -s)] fill];
			}
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
