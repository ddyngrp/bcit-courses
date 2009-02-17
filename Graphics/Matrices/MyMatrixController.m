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
	NSLog(@"start");
	NSArray * array;
	
	Matrix * m1 = [Matrix newWithXRows:3 YRows:3];
	Matrix * m2 = [Matrix newWithXRows:3 YRows:3];
	
	NSLog(@"init matrix");
	
	[m1 atX:1 atY:0 put:@"A"];
	[m1 atX:1 atY:1 put:@"B"];
	[m1 atX:1 atY:2 put:@"C"];
	[m1 atX:2 atY:2 put:@"D"];
	[m1 atX:2 atY:0 put:@"E"];
	
	[m1 print];
	array = [m1 rowAt:2];
	
	NSLog(@"%@", array);
	[array replaceObjectAtIndex:1 withObject:@"kk"];
	NSLog(@"%@", array);
	
	[m1 putColumnAt:0 column:array];
	
	[m1 print];

	
	NSLog(@"start testing");
	
	if ([m1 containsObject:@"C"]) {
		NSLog(@"EQUAL");
	}
	else {
		NSLog(@"NOT EQUAL");
	}
}


@end
