//
//  Encryption.h
//  Encrypted Chat
//
//  Created by Steffen L. Norgren on 09-10-04.
//  Copyright 2009 Esurient Systems Inc.. All rights reserved.
//

#import <Cocoa/Cocoa.h>


@interface Encryption : NSObject {
	NSCharacterSet	*alpha;
	NSString		*input;
	NSMutableString	*output;
}

- (NSString *)encryptAffine:(NSString *)message multNum:(int)mult addNum:(int)add;
- (NSString *)decryptAffine:(NSString *)message multNum:(int)mult addNum:(int)add;
- (NSString *)encryptVigenere:(NSString *)message cipherKey:(NSString *)key;
- (NSString *)decryptVigenere:(NSString *)message cipherKey:(NSString *)key;

@end
