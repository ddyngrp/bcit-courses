//
//  Matrix.m
//  Matricies
//
//  Created by Steffen L. Norgren on 13/02/09.
//  Copyright 2009 Esurient Systems Inc.. All rights reserved.
//

#import "Matrix.h"
#import "MatrixOutofBoundException.h"
#import "MatrixEnumerator.h"

@implementation Matrix
+ (id)newWithXRows:(int)i YRows:(int)j {
    // return a new instance Matrix with size i x j
	return [[self alloc] initX:i initY:j];
}

- (void) release {
	[super release];
	
	// free the used memory
	[storage release];
}
 
- (void) print {
	int i = 0;
	int j = 0;
	
	// maxX and maxY are local,   variables of the class instance
	for (i = 0; i < [self maxX]; i++) {
		for (j = 0; j < [self maxY]; j++) {
			NSLog(@"[%d, %d] = <<%@>>", i, j, [self atX:i atY:j]);
		}
	}
}

- (id)initX:(int)i initY:(int)j {
	int x = 0;
	int y = 0;
 
	[super init];
	
	// save the size
	[self maxX:i];
	[self maxY:j];
	
	// create an array of array's
	// the underlying datastructure used is a NSMutableArray
	// storage is private variable
	
	storage = [NSMutableArray arrayWithCapacity: j];
	
 	
	for (x = 0; x <= j; x++) {
		[storage insertObject:[NSMutableArray arrayWithCapacity:i ] atIndex:x];
		for (y = 0; y <= i; y++) {
			// initialize each element with something
		 	[[storage objectAtIndex:x] insertObject:@"" atIndex:y];
		}
	}
	
	// make sure we don't get garabage collected after a RunLoop
	[storage retain];
	return self;
}

- (void)atX:(int)i atY:(int)j put:(id)obj {
	// when the boundaries of a Matrix are not respected --> throw an exception
	
	if (i < 0 || i > [self maxX] - 1) {
		[MatrixOutofBoundException raise];
	}
	if (j < 0 || j > [self maxY] - 1) {
		[MatrixOutofBoundException raise];
	}
	
	[[storage objectAtIndex:j] replaceObjectAtIndex:i withObject:obj];
}

- (id)atX:(int)i atY:(int)j {
	// when the boundaries of a Matrix are not respected --> throw an exception
	
	if (i < 0 || i > [self maxX] - 1) {
		[MatrixOutofBoundException raise];
	}
	if (j < 0 || j > [self maxY] - 1) {
		[MatrixOutofBoundException raise];
	}
	
	return [[storage objectAtIndex:j] objectAtIndex:i];
}

- (BOOL)isEqual:(Matrix *)m {
	NSEnumerator * enum1;
	NSEnumerator * enum2;
	
	id obj1;
	id obj2;
	BOOL isEqual = YES;
	
	if ([self maxX] == [m maxX] && [self maxY] == [m maxY]) {
		// same size
		enum1 = [self objectEnumerator];
		enum2 = [m objectEnumerator];
		
		// enumerate over both matrices
		while ((obj1 = [enum1 nextObject]) != nil) {
			obj2 = [enum2 nextObject];
			// using the isEqual method on both objects
			if (![obj1 isEqual:obj2]) {
				isEqual = NO;
			}
		}
		[enum1 release];
		[enum2 release];
		 
		return isEqual;
	}
	else {
		// if they are not of the same size then the matrices cannot be equal
		return NO;
	}
}

- (BOOL)containsObject:(id)obj {
	NSEnumerator * enumerator;
	id obj2;
	
 	enumerator = [self objectEnumerator];
	while ((obj2 = [enumerator nextObject]) != nil) {
		if ([obj isEqual:obj2]) {
			return YES;
		}
	}
	
	return NO;
}

- (NSArray *)rowAt:(int)i {
	NSMutableArray * vector;
	int j = 0;
	
	vector = [NSMutableArray arrayWithCapacity:[self maxX]];
	for (j = 0; j < [self maxX]; j++) {
		[vector addObject:[self atX:j atY:i]];
	}
	
	return vector;
}

- (NSArray *)columnAt:(int)i {
	NSMutableArray * vector;
	int j = 0;
	
	vector = [NSMutableArray arrayWithCapacity:[self maxY]];
	for (j = 0 ;j < [self maxY]; j++) {
		[vector addObject:[self atX:i atY:j]];
	}
	
	return vector;
}

- (void)putRowAt:(int)i row:(NSArray *)row {
	// note: the row can be smaller than the row size of the Matrix
 	int j = 0;
	
	// iterate 
	for (j = 0; j < [self maxX]; j++) {
		// row index of matrix is higher than the size of the row
		if (j >= [row count]) {
			return;
		}
		
		[self atX:j atY:i put:[row objectAtIndex:j]];
	}
	return;
}

- (void)putColumnAt:(int)i column:(NSArray *)column {
	// note: the column can be smaller than the column size of the Matrix
	int j = 0;
	
	for (j = 0; j < [self maxY]; j++) {
		if (j >= [column count]) {
			return;
		}
		
		[self atX:i atY:j put:[column objectAtIndex:j]];
	}
	return;
}

- (void)transpose {
  // still need to implement	
}

- (NSEnumerator *)objectEnumerator {
	return [MatrixEnumerator newWithMatrix:self];
}

- (void)maxX:(int)x; {
	maxX = x ;
}

- (int) maxX {
	return maxX;
}

- (void)maxY:(int)y; {
	maxY = y;
}

- (int)maxY {
	return maxY;
}

@end
