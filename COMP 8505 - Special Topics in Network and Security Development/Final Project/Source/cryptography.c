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

int main (int argc, const char * argv[])
{
    return ERROR_NONE;
}

int generate_key()
{
	unsigned char tmp_key[KEY_LENGTH];	/* temporary key buffer */
	unsigned char tmp_iv[IV_LENGTH];	/* temporary initialization vector buffer */
	int i, fd_rand;

	/* open non-blocking random source */
	if ((fd_rand = open("/dev/urandom", O_RDONLY)) == ERROR_GENERAL)
		err(1, "open");

	/* read random bits into the key */
	if ((read(fd_rand, tmp_key, KEY_LENGTH)) == ERROR_GENERAL)
		err(1, "read");

	/* read random bits into the initialization vector */
	if ((read(fd_rand, tmp_iv, IV_LENGTH)) == ERROR_GENERAL)
		err(1, "read");

	/* print key in a copy/paste friendly array */
	printf("%d-bit tmp_key:\n{", KEY_LENGTH * 8);
	for (i = 0; i < KEY_LENGTH; i++) {
		if (i != KEY_LENGTH - 1)
			printf("%d, ", tmp_key[i]);
		else
			printf("%d", tmp_key[i]);
	}
	printf("}\n ------ \n");

	/* print initialization vector in a copy/paste friendly array*/
	printf("Initialization Vector:\n{");
	for (i = 0; i < IV_LENGTH; i++) {
		if (i != IV_LENGTH - 1)
			printf("%d, ", tmp_iv[i]);
		else
			printf("%d", tmp_iv[i]);
	}
	printf("}\n ------ \n");

	close(fd_rand);

	return ERROR_NONE;
}

char *encrypt_string(char *string)
{
	int olen, tlen;
	unsigned char *encrypted;
	EVP_CIPHER_CTX ctx;

	EVP_CIPHER_CTX_init(&ctx);
	EVP_EncryptInit(&ctx, EVP_bf_cbc(), key, iv);

	if ((encrypted = malloc(strlen(string) + 1)) == NULL)
			err(1, "malloc");

	if (EVP_EncryptUpdate(&ctx, encrypted, &olen, (unsigned char *)string,
				strlen(string)) != TRUE)
	{
		fprintf(stderr, "error in decrypt update\n");
		exit(ERROR_ENCRYPT);
	}

	if (EVP_EncryptFinal(&ctx, encrypted + olen, &tlen) != TRUE)
	{
		fprintf(stderr, "error in decrypt final\n");
		exit(ERROR_ENCRYPT);
	}

	EVP_CIPHER_CTX_cleanup (&ctx);

	return (char *)encrypted;
}

char *decrypt_string(char *string)
{
	int olen, tlen;
	unsigned char *decrypted;
	EVP_CIPHER_CTX ctx;

	EVP_CIPHER_CTX_init(&ctx);
	EVP_DecryptInit(&ctx, EVP_bf_cbc(), key, iv);

	if ((decrypted = malloc(strlen(string) + 1)) == NULL)
		err(1, "malloc");

	if (EVP_DecryptUpdate(&ctx, decrypted, &olen, (unsigned char *)string,
				strlen(string)) != TRUE)
	{
		fprintf(stderr, "error in decrypt update\n");
		exit(ERROR_DECRYPT);
	}

	if (EVP_DecryptFinal(&ctx, decrypted + olen, &tlen) != TRUE)
	{
		fprintf(stderr, "error in decrypt final\n");
		exit(ERROR_DECRYPT);
	}

	EVP_CIPHER_CTX_cleanup(&ctx);

	return (char *)decrypted;
}

int encrypt_file(int fd_in, int fd_out)
{
	return ERROR_NONE;
}

int decrypt_file(int fd_in, int fd_out)
{
	return ERROR_NONE;
}
