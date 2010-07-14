/*-----------------------------------------------------------------------------
 * cryptography.h - Cryptographic Utilities
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

#ifndef CRYPTOGRAPHY_H
#define CRYPTOGRAPHY_H

#include "common.h"

#include <openssl/evp.h>
#include <openssl/aes.h>

/* error codes */
#define ERROR_ENCRYPT	-2
#define ERROR_DECRYPT	-3

/* defaults */
#define AES_ROUNDS	16
#define KEY_SIZE	32		/* 256-bytes */
#define IN_SIZE		1024	/* file chunks */
#define OUT_SIZE	1040	/* AES file chunks */

/* function prototypes */
void test_crypto(void);
int aes_init(EVP_CIPHER_CTX *, EVP_CIPHER_CTX *);
unsigned char *aes_encrypt(EVP_CIPHER_CTX *, unsigned char *, int *);
unsigned char *aes_decrypt(EVP_CIPHER_CTX *, unsigned char *, int *);
int file_encrypt(FILE *, FILE *);
int file_decrypt(FILE *, FILE *);

#endif
