//
//  MatrixEnumerator.h
//  Matricies
//
//  Created by Steffen L. Norgren on 13/02/09.
//  Copyright 2009 Esurient Systems Inc.. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <Foundation/NSArray.h>
#import "Matrix.h"

#define BYROW 0
#define BYCOLUMN 1

@interface MatrixEnumerator : NSEnumerator {
	int i;
	int j;
	BOOL traversalOrder;
	Matrix * m;
}

+ (id)newWithMatrix:(Matrix *)myMatrix;

- (void)setTraversalOrder:(BOOL)order;
- (id)init:(Matrix *)myMatrix;
 
@end
