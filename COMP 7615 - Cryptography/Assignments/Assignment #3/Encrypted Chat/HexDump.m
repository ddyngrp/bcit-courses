//
//  HexDump.m
//  Encrypted Chat
//
//  Created by Steffen L. Norgren on 09-11-24.
//  Copyright 2009 Esurient Systems Inc.. All rights reserved.
//

#import "HexDump.h"


@implementation NSData (HexDump)

/**
 * Encodes the current data in base64, and creates and returns an NSString from the result.
 * This is the same as piping data through "... | openssl enc -base64" on the command line.
 *
 * Code courtesy of DaveDribin (http://www.dribin.org/dave/)
 * Taken from http://www.cocoadev.com/index.pl?BaseSixtyFour
 **/
- (NSString *)encodeBase64
{
    return [self encodeBase64WithNewlines: YES];
}

/**
 * Encodes the current data in base64, and creates and returns an NSString from the result.
 * This is the same as piping data through "... | openssl enc -base64" on the command line.
 *
 * Code courtesy of DaveDribin (http://www.dribin.org/dave/)
 * Taken from http://www.cocoadev.com/index.pl?BaseSixtyFour
 **/
- (NSString *)encodeBase64WithNewlines:(BOOL)encodeWithNewlines
{
    // Create a memory buffer which will contain the Base64 encoded string
    BIO * mem = BIO_new(BIO_s_mem());
    
    // Push on a Base64 filter so that writing to the buffer encodes the data
    BIO * b64 = BIO_new(BIO_f_base64());
    if (!encodeWithNewlines)
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    mem = BIO_push(b64, mem);
    
    // Encode all the data
    BIO_write(mem, [self bytes], [self length]);
    BIO_flush(mem);
    
    // Create a new string from the data in the memory buffer
    char * base64Pointer;
    long base64Length = BIO_get_mem_data(mem, &base64Pointer);
	
	// The base64pointer is NOT null terminated.
	
	NSData * base64data = [NSData dataWithBytesNoCopy:base64Pointer length:base64Length freeWhenDone:NO];
	NSString * base64String = [[NSString alloc] initWithData:base64data encoding:NSUTF8StringEncoding];
	
    // Clean up and go home
	BIO_free_all(mem);
	return [base64String autorelease];
}

- (NSData *)decodeBase64
{
    return [self decodeBase64WithNewLines:YES];
}

- (NSData *)decodeBase64WithNewLines:(BOOL)encodedWithNewlines
{
    // Create a memory buffer containing Base64 encoded string data
    BIO * mem = BIO_new_mem_buf((void *) [self bytes], [self length]);
	
    // Push a Base64 filter so that reading from the buffer decodes it
    BIO * b64 = BIO_new(BIO_f_base64());
    if (!encodedWithNewlines)
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    mem = BIO_push(b64, mem);
	
    // Decode into an NSMutableData
    NSMutableData * data = [NSMutableData data];
    char inbuf[512];
    int inlen;
    while ((inlen = BIO_read(mem, inbuf, sizeof(inbuf))) > 0)
        [data appendBytes: inbuf length: inlen];
	
    // Clean up and go home
    BIO_free_all(mem);
    return data;
}

- (NSString *)hexval
{
    NSMutableString *hex = [NSMutableString string];
    unsigned char *bytes = (unsigned char *)[self bytes];
    char temp[3];
    int i = 0;
	
    for (i = 0; i < [self length]; i++) {
        temp[0] = temp[1] = temp[2] = 0;
        (void)sprintf(temp, "%02x", bytes[i]);
        [hex appendString:[NSString stringWithUTF8String:temp]];
    }
	
    return hex;
}

- (NSString *)hexdump
{
    NSMutableString *ret=[NSMutableString stringWithCapacity:[self length]*2];
    /* dumps size bytes of *data to string. Looks like:
	 * [0000] 75 6E 6B 6E 6F 77 6E 20
	 *                  30 FF 00 00 00 00 39 00 unknown 0.....9.
	 * (in a single line of course)
	 */
    unsigned int size= [self length];
    const unsigned char *p = [self bytes];
    unsigned char c;
    int n;
    char bytestr[4] = {0};
    char addrstr[10] = {0};
    char hexstr[ 16*3 + 5] = {0};
    char charstr[16*1 + 5] = {0};
    for(n=1;n<=size;n++) {
        if (n%16 == 1) {
            /* store address for this line */
            snprintf(addrstr, sizeof(addrstr), "%.4x",
                     (unsigned int)((long)p-(long)self) );
        }
        
        c = *p;
        if (isalnum(c) == 0) {
            c = '.';
        }
        
        /* store hex str (for left side) */
        snprintf(bytestr, sizeof(bytestr), "%02X ", *p);
        strncat(hexstr, bytestr, sizeof(hexstr)-strlen(hexstr)-1);
        
        /* store char str (for right side) */
        snprintf(bytestr, sizeof(bytestr), "%c", c);
        strncat(charstr, bytestr, sizeof(charstr)-strlen(charstr)-1);
        
        if(n%16 == 0) {
            /* line completed */
            //printf("[%4.4s]   %-50.50s  %s\n", addrstr, hexstr, charstr);
            [ret appendString:[NSString stringWithFormat:@"[%4.4s]   %-50.50s  %s\n",
							   addrstr, hexstr, charstr]];
            hexstr[0] = 0;
            charstr[0] = 0;
        } else if(n%8 == 0) {
            /* half line: add whitespaces */
            strncat(hexstr, "  ", sizeof(hexstr)-strlen(hexstr)-1);
            strncat(charstr, " ", sizeof(charstr)-strlen(charstr)-1);
        }
        p++; /* next byte */
    }
    
    if (strlen(hexstr) > 0) {
        /* print rest of buffer if not empty */
        //printf("[%4.4s]   %-50.50s  %s\n", addrstr, hexstr, charstr);
        [ret appendString:[NSString stringWithFormat:@"[%4.4s]   %-50.50s  %s\n",
						   addrstr, hexstr, charstr]];
    }
    return ret;
}

@end
