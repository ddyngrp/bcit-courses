/*-----------------------------------------------------------------------------
 * SOURCE FILE:	Encryption.m
 * 
 * PROGRAM:     Encrypted Chat
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * NOTES: This class manages encryption and decryption of strings.
 *
 *---------------------------------------------------------------------------*/

#import "Encryption.h"

#define FORMAT(format, ...) [NSString stringWithFormat:(format), ##__VA_ARGS__]


@implementation Encryption

/*-----------------------------------------------------------------------------
 * FUNCTION:    init
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (id)init
 * 
 * RETURNS: The delegate id for this class.
 * 
 * NOTES: Initializes the class and allocates space for the input and output
 *        strings.
 *
 *----------------------------------------------------------------------------*/
- (id)init
{
	if (self = [super init]) {
		input = [NSString alloc];
		output = [NSMutableString alloc];
	}

	return self;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    dealloc
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (void)dealloc
 * 
 * RETURNS: void
 * 
 * NOTES: Handles garbage collection.
 *
 *----------------------------------------------------------------------------*/
- (void)dealloc
{
	[input release];
	[output release];
	[super dealloc];
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (NSString *)encryptAffine:(NSString *)message multNum:(int)mult
 *                                        addNum:(int)add;
 *                          message: the string to be encrypted
 *                          mult: the affine multiplier
 *                          add: addition to the shift
 * 
 * RETURNS: Encrypted string
 * 
 * NOTES: Encrypts a string using the Affine cipher.
 *
 *----------------------------------------------------------------------------*/
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

/*-----------------------------------------------------------------------------
 * FUNCTION:    decryptAffine
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (NSString *)decryptAffine:(NSString *)message multNum:(int)mult
 *                                        addNum:(int)add;
 *                          message: the string to be decrypted
 *                          mult: the affine multiplier
 *                          add: addition to the shift
 * 
 * RETURNS: Decrypted string
 * 
 * NOTES: Decrypts a string encrypted using the Affine cipher.
 *
 *----------------------------------------------------------------------------*/
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

/*-----------------------------------------------------------------------------
 * FUNCTION:    encryptVigenere
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (NSString *)encryptVigenere:(NSString *)message
 *                                          cipherKey:(NSString *)key;
 *                         message: message to be encrypted
 *                         key: the encrypton key
 * 
 * RETURNS: Encrypted string
 * 
 * NOTES: Encrypts a string using the Vigenère cipher.
 *
 *----------------------------------------------------------------------------*/
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

/*-----------------------------------------------------------------------------
 * FUNCTION:    decryptVigenere
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren
 * 
 * PROGRAMMER:  Steffen L. Norgren
 * 
 * INTERFACE:   (NSString *)decryptVigenere:(NSString *)message
 *                                          cipherKey:(NSString *)key;
 *                         message: message to be decrypted
 *                         key: the encrypton key
 * 
 * RETURNS: Decrypted string
 * 
 * NOTES: Decrypts a string encrypted with the Vigenère cipher.
 *
 *----------------------------------------------------------------------------*/
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
