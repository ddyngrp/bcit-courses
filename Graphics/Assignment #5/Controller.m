//
//  Controller.m
//  Assignment #5
//
//  Created by Steffen L. Norgren on 17/02/09.
//  Copyright 2009 Esurient Systems Inc.. All rights reserved.
//

#import "Controller.h"


@implementation Controller

- (void)awakeFromNib {
	// Read Data into our matricies
	if ([self readPoints:[[[NSBundle mainBundle] resourcePath] stringByAppendingString:@"/Qpoints3D.dat"]] == NO) {
		NSLog(@"Unable to read Qpoints.dat");
	}
	if ([self readLines:[[[NSBundle mainBundle] resourcePath] stringByAppendingString:@"/Qlines3D.dat"]] == NO) {
		NSLog(@"Unable to read Qlines.dat");
	}
}

+ (Matrix *)m_lines {
	return [self m_lines];
}

+ (Matrix *)m_points {
	return [self m_points];
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
	m_points = [Matrix newWithXRows:3 YRows:[newPoints count]];
	
	// Fill the new matrix with the vales from the array
	for (i = 0; i < [newPoints count]; i++) {
		[m_points atX:0 atY:i put:[NSNumber numberWithFloat:
								   [[[newPoints objectAtIndex:i] objectForKey:@"x"] floatValue]]];
		[m_points atX:1 atY:i put:[NSNumber numberWithFloat:
								   [[[newPoints objectAtIndex:i] objectForKey:@"y"] floatValue]]];
		[m_points atX:2 atY:i put:[NSNumber numberWithFloat:
								   [[[newPoints objectAtIndex:i] objectForKey:@"z"] floatValue]]];
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

@end
