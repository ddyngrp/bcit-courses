//
//  AES.h
//  Encrypted Chat
//
//  Created by Steffen L. Norgren on 09-11-24.
//  Copyright 2009 Esurient Systems Inc.. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <openssl/aes.h>
#import <openssl/evp.h>
#import <openssl/rand.h>
#import <openssl/rsa.h>
#import <openssl/engine.h>
#import <openssl/sha.h>
#import <openssl/pem.h>
#import <openssl/bio.h>
#import <openssl/err.h>
#import <openssl/ssl.h>
#import <openssl/md5.h>

@interface NSData (AES)

- (NSData *)aesEncryptWithKey:(NSString *)key;
- (NSData *)aesDecryptWithKey:(NSString *)key;
- (NSData *)getSHA1ForData:(NSData *)d;

@end
