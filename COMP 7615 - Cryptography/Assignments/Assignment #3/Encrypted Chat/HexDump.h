//
//  HexDump.h
//  Encrypted Chat
//
//  Created by Steffen L. Norgren on 09-11-24.
//  Copyright 2009 Esurient Systems Inc.. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <openssl/evp.h>

@interface NSData (HexDump)
- (NSString *)encodeBase64;
- (NSString *)encodeBase64WithNewlines:(BOOL)encodeWithNewlines;
- (NSData *)decodeBase64;
- (NSData *)decodeBase64WithNewLines:(BOOL)decodeWithNewLines;
- (NSString *)hexval;
- (NSString *)hexdump;
@end
