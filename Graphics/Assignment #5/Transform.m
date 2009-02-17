//
//  Transform.m
//  Assignment #5
//
//  Created by Steffen L. Norgren on 13/02/09.
//  Copyright 2009 Esurient Systems Inc.. All rights reserved.
//

#import "Transform.h"
#import "Matrices.h"


@implementation Transform

- (id)initWithFrame:(NSRect)frame {
	[super initWithFrame:frame];
	
    if (self) {
        [self setPoints:[NSMutableArray array]];
		[self setLines:[NSMutableArray array]];
		
		if ([self readPoints:[[[NSBundle mainBundle] resourcePath] stringByAppendingString:@"/Qpoints3D.dat"]] == NO) {
			NSLog(@"Unable to read Qpoints.dat");
		}
		if ([self readLines:[[[NSBundle mainBundle] resourcePath] stringByAppendingString:@"/Qlines3D.dat"]] == NO) {
			NSLog(@"Unable to read Qlines.dat");
		}
	}
	
	return self;
}

- (void)drawRect:(NSRect)rect {
	NSBezierPath * aPath = [NSBezierPath bezierPath];
	int lCount, p1, p2;
	float x1, y1, x2, y2;
	
	[NSBezierPath setDefaultLineWidth:1.0];
	
	lCount = [lines count];
	
	for (int i = 0; i < lCount; i++) {
		p1 = [[[lines objectAtIndex:i] objectForKey:@"p1"] intValue];
		p2 = [[[lines objectAtIndex:i] objectForKey:@"p2"] intValue];
		
		x1 = [[[points objectAtIndex:p1] objectForKey:@"x"] floatValue];
		y1 = [[[points objectAtIndex:p1] objectForKey:@"y"] floatValue];
		x2 = [[[points objectAtIndex:p2] objectForKey:@"x"] floatValue];
		y2 = [[[points objectAtIndex:p2] objectForKey:@"y"] floatValue];
		
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
    [self setPoints:nil];
    [self setLines:nil];
	[super dealloc];
}

- (NSMutableArray *)points {
    return points;
}

- (NSMutableArray *)lines {
    return lines;
}

- (void)setPoints:(NSMutableArray *)newPoints {
    [newPoints retain];
    [points release];
    points = newPoints;
}

- (void)setLines:(NSMutableArray *)newLines {
    [newLines retain];
    [lines release];
    lines = newLines;
}

- (BOOL)readPoints:(NSString *)fileName {
	
	NSString * fileData = [NSString stringWithContentsOfFile: fileName];
	
	if (nil == fileData) {
		return NO;
	}
	
	NSScanner * scanner = [NSScanner scannerWithString:fileData];
	[scanner setCharactersToBeSkipped:[NSCharacterSet characterSetWithCharactersInString:@"\r\n "]];
	NSMutableArray *newPoints = [NSMutableArray array];
	float x, y, z;
	
	while ([scanner scanFloat:&x] && [scanner scanFloat:&y] && [scanner scanFloat:&z]) {
        [newPoints addObject: [NSMutableDictionary dictionaryWithObjectsAndKeys:
							   [NSNumber numberWithFloat:x], @"x",
							   [NSNumber numberWithFloat:y], @"y", 
							   [NSNumber numberWithFloat:z], @"z", 
							   nil]];
    }
    [self setPoints:newPoints];
	
	return YES;
}

- (BOOL)readLines:(NSString *)fileName {
	
	NSString * fileData = [NSString stringWithContentsOfFile: fileName];
	
	if (nil == fileData) {
		return NO;
	}
	
	NSScanner * scanner = [NSScanner scannerWithString:fileData];
	[scanner setCharactersToBeSkipped:[NSCharacterSet characterSetWithCharactersInString:@"\r\n "]];
	NSMutableArray *newLines = [NSMutableArray array];
	int p1, p2;
	
	while ([scanner scanInt:&p1] && [scanner scanInt:&p2]) {
        [newLines addObject: [NSMutableDictionary dictionaryWithObjectsAndKeys:
							  [NSNumber numberWithInt:p1], @"p1",
							  [NSNumber numberWithInt:p2], @"p2", 
							  nil]];
    }
    [self setLines:newLines];
	
	return YES;
}

@end
