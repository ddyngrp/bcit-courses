//
//  MatrixOutofBoundException.h
//  Matricies
//
//  Created by Steffen L. Norgren on 13/02/09.
//  Copyright 2009 Esurient Systems Inc.. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <Foundation/NSException.h>

@interface MatrixOutofBoundException : NSException {

}

+ (void) raise;

@end
