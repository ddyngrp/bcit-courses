//
//  Matrix.h
//  Matricies
//
//  Created by Steffen L. Norgren on 13/02/09.
//  Copyright 2009 Esurient Systems Inc.. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <Foundation/NSArray.h>
 

@interface Matrix : NSObject {

@private
	int maxX;
	int maxY;
	NSMutableArray * storage;
}

+ (id)newWithXRows:(int)i YRows:(int)j;
- (id)initX:(int)i initY:(int)j;
- (void)atX:(int)i atY:(int)j put:(id)obj;
- (id)atX:(int)i atY:(int)j;

- (BOOL)isEqual:(Matrix *)m;
- (BOOL)containsObject:(id)obj;

- (NSArray *)rowAt:(int)i;
- (NSArray *)columnAt:(int)i;

- (void)putRowAt:(int)i row:(NSArray *)row;			// not yet implemented
- (void)putColumnAt:(int)i column:(NSArray *)row;	// not yet implemented

- (void)transpose;	// not yet implemented

- (NSEnumerator *)objectEnumerator;

- (void)maxX:(int)x;
- (int)maxX;
- (void)maxY:(int)y;
- (int)maxY;

- (void)print;

@end
