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

#ifndef CRYPT_H
#define CRYPT_H

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
#include <err.h>

#include <openssl/blowfish.h>
#include <openssl/evp.h>

/* error codes */
#define ERROR_NONE		 0
#define ERROR_GENERAL	-1
#define ERROR_ENCRYPT	-2
#define ERROR_DECRYPT	-3

/* true/false */
#define TRUE	1
#define FALSE	0

/* defaults */
#define KEY_LENGTH	56	/* 448-bit key (maximum blowfish key length) */
#define IV_LENGTH	8	/* 64-bit initialization vector */
#define IN_SIZE		1024
#define OUT_SIZE	IN_SIZE + 8
#define FLAGS_IN	O_RDONLY
#define FLAGS_OUT	O_RDONLY | O_WRONLY | O_CREAT
#define MODE		S_IRUSR | S_IWUSR

/* function prototypes */
int generate_key(void);
char *encrypt_string(char *);
char *decrypt_string(char *);
int encrypt_file(int, int);
int decrypt_file(int, int);

/* globals */
unsigned char key[] = {143, 217, 186, 251, 227, 8, 27, 160, 135, 64, 12, 187, 59, 38, 90, 23, 37, 101, 238, 204, 16, 50, 26, 244, 54, 173, 202, 142, 121, 222, 56, 56, 32, 92, 242, 230, 190, 53, 235, 101, 232, 102, 83, 173, 49, 239, 211, 251, 251, 225, 120, 14, 58, 197, 160, 235};
unsigned char iv[] = {90, 210, 231, 11, 143, 73, 130, 20};

#endif
