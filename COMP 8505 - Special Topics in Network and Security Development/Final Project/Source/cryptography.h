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
unsigned char key[] = {0xBE, 0x63, 0x93, 0x30, 0xD7, 0xB3, 0x24, 0x85, 0xC1, 0xE1, 0x3D, 0x1C, 0x69, 0xC4, 0xEB, 0xDF, 0x1, 0xB5, 0xD0, 0x62, 0x88, 0x9A, 0xB, 0xAD, 0xD9, 0xC5, 0x7E, 0x2E, 0x73, 0x16, 0xC, 0x51, 0xC1, 0x1E, 0x11, 0x6A, 0xBE, 0x38, 0xF1, 0xDD, 0xAC, 0xDB, 0x2A, 0xBE, 0x15, 0x15, 0x70, 0x78, 0x2F, 0x79, 0xC3, 0xFE, 0xFF, 0x81, 0x86, 0xEF};
unsigned char iv[] = {0x39, 0xB6, 0xAA, 0x1F, 0xEE, 0x4D, 0x1F, 0xB5};

#endif
