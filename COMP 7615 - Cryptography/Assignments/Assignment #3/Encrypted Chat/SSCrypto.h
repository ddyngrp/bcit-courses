/*-----------------------------------------------------------------------------
 * SOURCE FILE:	SSCrypto.h
 * 
 * PROGRAM:     Encrypted Chat
 * 
 * DATE:        November 24, 2009
 * 
 * REVISIONS:   November 24, 2009 - Steffen L. Norgren <ironix@trollop.org>
 *                                  Created proper headers & comments.
 * 
 * DESIGNER:    Ed Silva
 * 
 * PROGRAMMER:  Ed Silva
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * NOTES: Header file for the SSCrypto class.
 *
 *---------------------------------------------------------------------------*/

#import <Foundation/Foundation.h>
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

@interface NSData (HexDump)
- (NSString *)encodeBase64;
- (NSString *)encodeBase64WithNewlines:(BOOL)encodeWithNewlines;
- (NSData *)decodeBase64;
- (NSData *)decodeBase64WithNewLines:(BOOL)decodeWithNewLines;
- (NSString *)hexval;
- (NSString *)hexdump;
@end

@interface SSCrypto : NSObject
{
    NSData *symmetricKey;
    NSData *cipherText;
    NSData *clearText;
	NSData *publicKey;
	NSData *privateKey;
	
	BOOL isSymmetric;
}

- (id)init;
- (id)initWithSymmetricKey:(NSData *)k;
- (id)initWithPublicKey:(NSData *)pub;
- (id)initWithPrivateKey:(NSData *)priv;
- (id)initWithPublicKey:(NSData *)pub privateKey:(NSData *)priv;

- (BOOL)isSymmetric;
- (void)setIsSymmetric:(BOOL)flag;

- (NSData *)symmetricKey;
- (void)setSymmetricKey:(NSData *)k;

- (NSData *)publicKey;
- (void)setPublicKey:(NSData *)k;

- (NSData *)privateKey;
- (void)setPrivateKey:(NSData *)k;

- (NSData *)clearTextAsData;
- (NSString *)clearTextAsString;
- (void)setClearTextWithData:(NSData *)c;
- (void)setClearTextWithString:(NSString *)c;

- (NSData *)cipherTextAsData;
- (NSString *)cipherTextAsString;
- (void)setCipherText:(NSData *)c;

- (NSData *)decrypt;
- (NSData *)decrypt:(NSString *)cipherName;

- (NSData *)verify;

- (NSData *)encrypt;
- (NSData *)encrypt:(NSString *)cipherName;

- (NSData *)sign;

- (NSData *)digest:(NSString *)digestName;

+ (NSData *)generateRSAPrivateKeyWithLength:(int)length;
+ (NSData *)generateRSAPublicKeyFromPrivateKey:(NSData *)privateKey;
+ (NSData *)getKeyDataWithLength:(int)length;
+ (NSData *)getKeyDataWithLength:(int)length fromPassword:(NSString *)pass withSalt:(NSString *)salt;
+ (NSData *)getKeyDataWithLength:(int)length fromPassword:(NSString *)pass withSalt:(NSString *)salt withIterations:(int)count;
+ (NSData *)getSHA1ForData:(NSData *)d;
+ (NSData *)getMD5ForData:(NSData *)d;

@end
