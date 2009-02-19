//
//  Transform.m
//  Assignment #5
//
//  Created by Steffen L. Norgren on 13/02/09.
//  Copyright 2009 Esurient Systems Inc.. All rights reserved.
//

#import "Transform.h"


@implementation Transform

- (id)initWithFrame:(NSRect)frame {
	[super initWithFrame:frame];
	int i, j;
	
	// Read Data into our matricies
	if ([self readPoints:[[[NSBundle mainBundle] resourcePath] stringByAppendingString:@"/Qpoints.dat"]] == NO) {
		NSLog(@"Unable to read Qpoints.dat");
	}
	if ([self readLines:[[[NSBundle mainBundle] resourcePath] stringByAppendingString:@"/Qlines.dat"]] == NO) {
		NSLog(@"Unable to read Qlines.dat");
	}
	
	// Create an identity matrix
	m_product = [Matrix newWithXRows:4 YRows:4];
	for (i = 0; i < 4; i++) {
		[m_product atX:i atY:j put:[NSNumber numberWithFloat:0.0]];
	}
	
	[m_product atX:0 atY:0 put:[NSNumber numberWithFloat:1.0]];
	[m_product atX:1 atY:1 put:[NSNumber numberWithFloat:1.0]];
	[m_product atX:2 atY:2 put:[NSNumber numberWithFloat:1.0]];
	[m_product atX:3 atY:3 put:[NSNumber numberWithFloat:1.0]];

	return self;
}

- (void)drawRect:(NSRect)rect {
	NSBezierPath * aPath = [NSBezierPath bezierPath];
	Matrix * m_draw = [Matrix newWithMultiply:m_points m2:m_product];
	int p1, p2;
	float x1, y1, x2, y2;
	
	[NSBezierPath setDefaultLineWidth:1.0];
	
	for (int i = 0; i < [m_lines maxY]; i++) {
		p1 = [[m_lines atX:0 atY:i] intValue];
		p2 = [[m_lines atX:1 atY:i] intValue];
		
		x1 = [[m_draw atX:0 atY:p1] floatValue];
		y1 = [[m_draw atX:1 atY:p1] floatValue];
		x2 = [[m_draw atX:0 atY:p2] floatValue];
		y2 = [[m_draw atX:1 atY:p2] floatValue];
		
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

- (BOOL)readPoints:(NSString *)fileName {
	float x, y, z;
	int i;
	
	NSString * fileData = [NSString stringWithContentsOfFile: fileName];
	
	if (nil == fileData) {
		return NO;
	}
	
	NSScanner * scanner = [NSScanner scannerWithString:fileData];
	[scanner setCharactersToBeSkipped:[NSCharacterSet characterSetWithCharactersInString:@"\r\n "]];
	NSMutableArray * newPoints = [NSMutableArray array];
	
	while ([scanner scanFloat:&x] && [scanner scanFloat:&y] && [scanner scanFloat:&z]) {
        [newPoints addObject: [NSMutableDictionary dictionaryWithObjectsAndKeys:
							   [NSNumber numberWithFloat:x], @"x",
							   [NSNumber numberWithFloat:y], @"y", 
							   [NSNumber numberWithFloat:z], @"z", 
							   nil]];
    }
	
	// Set the size of the matrix
	m_points = [Matrix newWithXRows:4 YRows:[newPoints count]];
	
	// Fill the new matrix with the vales from the array
	for (i = 0; i < [newPoints count]; i++) {
		[m_points atX:0 atY:i put:[NSNumber numberWithFloat:
								   [[[newPoints objectAtIndex:i] objectForKey:@"x"] floatValue]]];
		[m_points atX:1 atY:i put:[NSNumber numberWithFloat:
								   [[[newPoints objectAtIndex:i] objectForKey:@"y"] floatValue]]];
		[m_points atX:2 atY:i put:[NSNumber numberWithFloat:
								   [[[newPoints objectAtIndex:i] objectForKey:@"z"] floatValue]]];
		[m_points atX:3 atY:i put:[NSNumber numberWithFloat:1.0]];
	}
	
	[newPoints removeAllObjects]; // clear the temporary array
	
	return YES;
}

- (BOOL)readLines:(NSString *)fileName {
	int p1, p2, i;
	
	NSString * fileData = [NSString stringWithContentsOfFile: fileName];
	
	if (nil == fileData) {
		return NO;
	}
	
	NSScanner * scanner = [NSScanner scannerWithString:fileData];
	[scanner setCharactersToBeSkipped:[NSCharacterSet characterSetWithCharactersInString:@"\r\n "]];
	NSMutableArray * newLines = [NSMutableArray array];
	
	while ([scanner scanInt:&p1] && [scanner scanInt:&p2]) {
        [newLines addObject: [NSMutableDictionary dictionaryWithObjectsAndKeys:
							  [NSNumber numberWithInt:p1], @"p1",
							  [NSNumber numberWithInt:p2], @"p2", 
							  nil]];
    }
	
	// Set the size of the matrix
	m_lines = [Matrix newWithXRows:2 YRows:[newLines count]];
	
	// Fill the new matrix with the vales from the array
	for (i = 0; i < [newLines count]; i++) {
		[m_lines atX:0 atY:i put:[NSNumber numberWithFloat:
								  [[[newLines objectAtIndex:i] objectForKey:@"p1"] intValue]]];
		[m_lines atX:1 atY:i put:[NSNumber numberWithFloat:
								  [[[newLines objectAtIndex:i] objectForKey:@"p2"] intValue]]];
	}
	
	[newLines removeAllObjects]; // clear the temporary array
	
	return YES;
}

- (void)dealloc {
	[super dealloc];
}

@end
