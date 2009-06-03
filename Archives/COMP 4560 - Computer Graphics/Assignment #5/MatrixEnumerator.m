//
//  MatrixEnumerator.m
//  Matricies
//
//  Created by Steffen L. Norgren on 13/02/09.
//  Copyright 2009 Esurient Systems Inc.. All rights reserved.
//

#import "MatrixEnumerator.h"


@implementation MatrixEnumerator


+ (id)newWithMatrix:(Matrix *)myMatrix {
	return [[self alloc] init:myMatrix];	
}

- (id)init:(Matrix *)myMatrix {
	// initialize the instance with default values
    [super init];
	i = 0;
	j = 0;
	m = myMatrix;
	traversalOrder = BYROW;
	
	return self;
}

- (id)nextObject {
	id obj;
	
	// passing the boundaries
	if (traversalOrder == BYROW) {
		if (j >= [m maxY]) {
			return nil;
		}
	}
	if (traversalOrder == BYCOLUMN) {
		if (i >= [m maxX]) {
			return nil;
		}
	}
	
	// get object
	obj = [m atX:i atY:j];
	
	// decide how to increment (byrow or bycolumn)
	if (traversalOrder == BYROW) {
		// row traversal
		i++;
		if (i >= [m maxX]) {
			j++;
			i = 0;
		}
	}
	else {
		// column traversal
		j++;
		if (j >= [m maxY]) {
			i++;
			j = 0;
		}
	}
	
	return obj;
}



- (NSArray *)allObjects {
	id obj;
	
	NSMutableArray * myArray = [NSMutableArray new];
	
	// iterate over the remaining objects and put them in an Array
	while ((obj = [self nextObject]) != nil) {
		[myArray addObject:obj];
	}
	return myArray;
}

- (void)setTraversalOrder:(BOOL)order {
	traversalOrder = order;
}


@end
