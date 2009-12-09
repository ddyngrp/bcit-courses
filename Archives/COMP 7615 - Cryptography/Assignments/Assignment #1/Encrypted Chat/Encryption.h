/*-----------------------------------------------------------------------------
 * SOURCE FILE:	Encryption.h
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
 * NOTES: This is the header file for the encryption class.
 *
 *---------------------------------------------------------------------------*/

#import <Cocoa/Cocoa.h>


@interface Encryption : NSObject {
	NSString		*input;
	NSMutableString	*output;
}

- (NSString *)encryptAffine:(NSString *)message multNum:(int)mult addNum:(int)add;
- (NSString *)decryptAffine:(NSString *)message multNum:(int)mult addNum:(int)add;
- (NSString *)encryptVigenere:(NSString *)message cipherKey:(NSString *)key;
- (NSString *)decryptVigenere:(NSString *)message cipherKey:(NSString *)key;

@end
