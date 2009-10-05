//
//  Encryption.m
//  Encrypted Chat
//
//  Created by Steffen L. Norgren on 09-10-04.
//  Copyright 2009 Esurient Systems Inc.. All rights reserved.
//

#import "Encryption.h"

#define FORMAT(format, ...) [NSString stringWithFormat:(format), ##__VA_ARGS__]


@implementation Encryption

- (id)init
{
	if (self = [super init]) {
		alpha = [NSCharacterSet characterSetWithCharactersInString:@"abcdefghijklmnopqrstuvwxyz"];
		input = [NSString alloc];
		output = [NSMutableString alloc];
	}

	return self;
}

- (void)dealloc
{
	[alpha release];
	[input release];
	[output release];
	[super dealloc];
}

- (NSString *)encryptAffine:(NSString *)message multNum:(int)mult addNum:(int)add;
{
	// Remove all non alphabetic characters from the string
	input = [[[message lowercaseString] componentsSeparatedByCharactersInSet:
			  [[NSCharacterSet letterCharacterSet] invertedSet]] componentsJoinedByString:@""];
	
	output = [[NSMutableString alloc] initWithCapacity:[input length]];

	// Loop through all characters in the message
	for (int i = 0; i < [input length]; i++) {
		// Get the current key character and shift so 'a' == 0
		char currentChar = [input characterAtIndex:i] - 97;
		
		// Apply the Affine formula and then shight back 97
		currentChar = (currentChar * mult + add) % 26 + 97;
		
		// Append to the encrypted string
		[output appendString:FORMAT(@"%c", currentChar)];
	}
	
	return [output lowercaseString];
}

- (NSString *)decryptAffine:(NSString *)message multNum:(int)mult addNum:(int)add;
{
	// Remove all non alphabetic characters from the string
	input = [[[message lowercaseString] componentsSeparatedByCharactersInSet:
			  [[NSCharacterSet letterCharacterSet] invertedSet]] componentsJoinedByString:@""];
	
	output = [[NSMutableString alloc] initWithCapacity:[input length]];
	
	// Set the default inverse
	int multInverse = 1;
	
	// Finde the inverse
    for (int i = 1; i <= 25; i += 2)
		if ( (mult * i) % 26 == 1)
			multInverse = i;
	
	// Loop through all characters in the message
	for (int i = 0; i < [input length]; i++) {
		// Get the current key character and shift so 'a' == 0
		char currentChar = [input characterAtIndex:i] - 97;
		
		// Apply the Affine formula and then shight back 97
		currentChar = ((multInverse * (currentChar + 26 - add)) % 26) + 97;
		
		// Append to the encrypted string
		[output appendString:FORMAT(@"%c", currentChar)];
	}
	
	return [output lowercaseString];
}

- (NSString *)encryptVigenere:(NSString *)message cipherKey:(NSString *)key;
{
	// Remove all non alphabetic characters from the string
	input = [[[message lowercaseString] componentsSeparatedByCharactersInSet:
			  [[NSCharacterSet letterCharacterSet] invertedSet]] componentsJoinedByString:@""];
	
	output = [[NSMutableString alloc] initWithCapacity:[input length]];
	
	// Loop through all characters in the message
	for (int i = 0; i < [input length]; i++) {
		// Get the current key character
		char currentKey = [key characterAtIndex:(i%[key length])];
		
		// Get the numeric value of the current key character
		int hash = currentKey - 97;
		
		// Shift the character in the message
		int n = [input characterAtIndex:i] + hash;
		
		// Cycle back if needed
		if (n > 122)
			n -= 26;
		
		// Append to the encrypted string
		[output appendString:FORMAT(@"%c", n)];
	}
	
	return [output lowercaseString];
}

- (NSString *)decryptVigenere:(NSString *)message cipherKey:(NSString *)key;
{
	// Remove all non alphabetic characters from the string
	input = [[[message lowercaseString] componentsSeparatedByCharactersInSet:
			  [[NSCharacterSet letterCharacterSet] invertedSet]] componentsJoinedByString:@""];
	
	output = [[NSMutableString alloc] initWithCapacity:[input length]];

	// Loop through all characters in the message
	for (int i = 0; i < [input length]; i++) {
		// Get the current key character
		char currentKey = [key characterAtIndex:(i%[key length])];
		
		// Get the numeric value of the current key character
		int hash = currentKey - 97;
		
		// Shift the character in the message
		int n = [input characterAtIndex:i] - hash;

		// Cycle back if needed
		if (n < 97)
			n += 26;
		
		// Append to the encrypted string
		[output appendString:FORMAT(@"%c", n)];
	}
	
	return [output lowercaseString];
}

@end
