//
//  Controller.h
//  Assignment #5
//
//  Created by Steffen L. Norgren on 17/02/09.
//  Copyright 2009 Esurient Systems Inc.. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "Matrix.h"

@interface Controller : NSObject {
@public
	Matrix * m_transform;
	Matrix * m_rotate;
	Matrix * m_sheer;
	Matrix * m_scale;

	Matrix * m_product;
	Matrix * m_points;
	Matrix * m_lines;
}

+ (Matrix *)m_lines;
+ (Matrix *)m_points;
- (BOOL)readPoints:(NSString *)fileName;
- (BOOL)readLines:(NSString *)fileName;


@end
