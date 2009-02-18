//
//  MatrixOutofBoundException.m
//  Matricies
//
//  Created by Steffen L. Norgren on 13/02/09.
//  Copyright 2009 Esurient Systems Inc.. All rights reserved.
//

#import "MatrixOutofBoundException.h"


@implementation MatrixOutofBoundException

+ (void) raise {
    [[super exceptionWithName:@"Matrix out of bound exception" 
					   reason:@"Matrix out bounds exception : out of bounds" 
					 userInfo:nil] raise];
}

@end
