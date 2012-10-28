//
//  MyMatrixController.m
//  Matricies
//
//  Created by Steffen L. Norgren on 13/02/09.
//  Copyright 2009 Esurient Systems Inc.. All rights reserved.
//

#import "MyMatrixController.h"
#import "Matrix.h"


@implementation MyMatrixController

- (void)awakeFromNib {
	Matrix * m1 = [Matrix newWithXRows:4 YRows:4];
	
	NSLog(@"init matrix");
	
	[m1 atX:0 atY:0 put:[NSNumber numberWithFloat:1.0]];
	[m1 atX:1 atY:0 put:[NSNumber numberWithFloat:2.0]];
	[m1 atX:2 atY:0 put:[NSNumber numberWithFloat:3.0]];
	[m1 atX:3 atY:0 put:[NSNumber numberWithFloat:4.0]];

	[m1 atX:0 atY:1 put:[NSNumber numberWithFloat:5.0]];
	[m1 atX:1 atY:1 put:[NSNumber numberWithFloat:6.0]];
	[m1 atX:2 atY:1 put:[NSNumber numberWithFloat:7.0]];
	[m1 atX:3 atY:1 put:[NSNumber numberWithFloat:8.0]];

	[m1 atX:0 atY:2 put:[NSNumber numberWithFloat:9.0]];
	[m1 atX:1 atY:2 put:[NSNumber numberWithFloat:10.0]];
	[m1 atX:2 atY:2 put:[NSNumber numberWithFloat:11.0]];
	[m1 atX:3 atY:2 put:[NSNumber numberWithFloat:12.0]];

	[m1 atX:0 atY:3 put:[NSNumber numberWithFloat:13.0]];
	[m1 atX:1 atY:3 put:[NSNumber numberWithFloat:14.0]];
	[m1 atX:2 atY:3 put:[NSNumber numberWithFloat:15.0]];
	[m1 atX:3 atY:3 put:[NSNumber numberWithFloat:16.0]];
	
	NSLog(@"multiply matrix");

	Matrix * prod = [Matrix newWithMultiply:m1 m2:m1];
	[prod print];
}


@end
