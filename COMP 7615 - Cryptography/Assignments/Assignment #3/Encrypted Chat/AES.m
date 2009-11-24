//
//  AES.m
//  Encrypted Chat
//
//  Created by Steffen L. Norgren on 09-11-24.
//  Copyright 2009 Esurient Systems Inc.. All rights reserved.
//

#import "AES.h"

@implementation NSData (AES)

- (NSData*)aesEncryptWithKey:(NSString*)key
{
	// Create a random 128-bit initialization vector
	srand(time(NULL));
	int ivIndex;
	unsigned char iv[16];
	for (ivIndex = 0; ivIndex < 16; ivIndex++)
		iv[ivIndex] = rand() & 0xff;
	
	// Calculate the 16-byte AES block padding
	int dataLength = [self length];
	int paddedLength = dataLength + (32 - (dataLength % 16));
	int totalLength = paddedLength + 16; // Data plus IV
	
	// Allocate enough space for the IV + ciphertext
	unsigned char *encryptedBytes = calloc(1, totalLength);
	// The first block of the ciphertext buffer is the IV
	memcpy(encryptedBytes, iv, 16);
	
	unsigned char *paddedBytes = calloc(1, paddedLength);
	memcpy(paddedBytes, [self bytes], dataLength);
	
	// The last 32-bit chunk is the size of the plaintext, which is encrypted with the plaintext
	int bigIntDataLength = NSSwapHostIntToBig(dataLength);
	memcpy(paddedBytes + (paddedLength - 4), &bigIntDataLength, 4);
	
	// Create the key from first 128-bits of the 160-bit password hash
	unsigned char keyDigest[20];
	
	[[self getSHA1ForData:[key dataUsingEncoding:NSUTF8StringEncoding]] getBytes:keyDigest length:20];
	
	AES_KEY aesKey;
	AES_set_encrypt_key(keyDigest, 128, &aesKey);
	
	// AES-128-cbc encrypt the data, filling in the buffer after the IV
	AES_cbc_encrypt(paddedBytes, encryptedBytes + 16, paddedLength, &aesKey, iv, AES_ENCRYPT);
	free(paddedBytes);
    
	return [NSData dataWithBytesNoCopy:encryptedBytes length:totalLength];
}

- (NSData*)aesDecryptWithKey:(NSString*)key
{
	NSData* dataStuff;
	return dataStuff;
}

- (NSData *)getSHA1ForData:(NSData *)d
{
    unsigned length = [d length];
    const void *buffer = [d bytes];
    unsigned char *md = (unsigned char *)calloc(SHA_DIGEST_LENGTH, sizeof(unsigned char));
    NSAssert((md != NULL), @"Cannot calloc memory for buffer.");
	
    (void)SHA1(buffer, length, md);
	
    return [NSData dataWithBytesNoCopy:md length:SHA_DIGEST_LENGTH freeWhenDone:YES];
}

@end
