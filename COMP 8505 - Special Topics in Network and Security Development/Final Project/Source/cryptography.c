/*-----------------------------------------------------------------------------
 * cryptography.c - Cryptographic Utilities
 * Copyright (C) 2010 Steffen L. Norgren <ironix@trollop.org>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *----------------------------------------------------------------------------*/

#include "cryptography.h"

int main(int argc, const char * argv[])
{
	return SUCCESS;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    aes_init
 * 
 * DATE:        July 2, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   aes_init(unsigned char *key_data, int key_data_length
 *                       unsigned char *salt, EVP_CIPHER_CTX *e_ctx,
 *                       EVP_CIPHER *d_ctx)
 *                  key_data        - data to be used to create a key
 *                  key_data_length - length of the key_data
 *                  salt            - salt to be added for taste
 *                  e_ctx           - OpenSSL cipher structure
 *                  d_ctx           - OpenSSL cipher structure
 * 
 * RETURNS:     SUCCESS or ERROR
 *
 * NOTES: Creates a 256-bit key and initializtion vector using the supplied key
 *        data. Salt may be added for taste. Fills in the encryption and
 *        decryption ctx objects.
 *----------------------------------------------------------------------------*/
int aes_init(unsigned char *key_data, int key_data_length, unsigned char *salt,
		EVP_CIPHER_CTX *e_ctx, EVP_CIPHER *d_ctx)
{
	

	return SUCCESS;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    aes_encrypt 
 * 
 * DATE:        July 2, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:  unsigned char *aes_encrypt(EVP_CIPHER_CTX *e_ctx,
 *                                        unsigned char *plaintext, int *length) 
 *                  e_ctx     - OpenSSL encryption cipher structure
 *                  plaintext - text to be encrypted
 *                  length    - length of plaintext
 * 
 * RETURNS:     Encrypted string
 *
 * NOTES: Encrypts *length bytes of data. All the data going in and out is
 *        considered binary.
 *----------------------------------------------------------------------------*/
unsigned char *aes_encrypt(EVP_CIPHER_CTX *e_ctx, unsigned char *plaintext, int *length)
{
	return NULL;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    aes_decrypt
 * 
 * DATE:        July 2, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   unsigned char *aes_decrypt(EVP_CIPHER_CTX *e_ctx,
 *                                       unsigned char *ciphertext, int *length)
 *                  e_ctx      - OpenSSL encryption cipher structure 
 *                  ciphertext - encrypted text to be decrypted
 *                  length     - length of ciphertext
 * 
 * RETURNS:     Decrypted string
 *
 * NOTES: Decrypts *length bytes of ciphertext. All the data going in and out
 *        is considered binary.
 *----------------------------------------------------------------------------*/
unsigned char *aes_decrypt(EVP_CIPHER_CTX *e_ctx, unsigned char *ciphertext, int *length)
{
	return NULL;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    file_encrypt
 * 
 * DATE:        July 2, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   int file_encrypt(int fd_in, int fd_out)
 *                  fd_in  - file to be encrypted
 *                  fd_out - destination of encrypted file
 * 
 * RETURNS:     SUCCESS or ERROR
 *
 * NOTES: Encrypts a fd_in file and saves it to fd_out.
 *----------------------------------------------------------------------------*/
int file_encrypt(int fd_in, int fd_out)
{
	return SUCCESS;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    file_decrypt
 * 
 * DATE:        July 2, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   int file_decrypt(int fd_in, int fd_out)
 *                  fd_in  - file to be decrypted
 *                  fd_out - destination of decrypted file
 * 
 * RETURNS:     SUCCESS or ERROR
 *
 * NOTES: Decrypts a fd_in file and saves it to fd_out.
 *----------------------------------------------------------------------------*/
int file_decrypt(int fd_in, int fd_out)
{
	return SUCCESS;
}
