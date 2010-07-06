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
	test_crypto();

	return SUCCESS;
}


/*-----------------------------------------------------------------------------
 * FUNCTION:    test_crypto
 * 
 * DATE:        July 2, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   test_crypto(void)
 * 
 * RETURNS:     void
 *
 * NOTES: Tests whether encryption/decryption is sane or not. 
 *----------------------------------------------------------------------------*/
void test_crypto(void)
{
	EVP_CIPHER_CTX encrypt, decrypt;
	char *input = "This is a test string to encrypt.";
	unsigned char *ciphertext;
	char *plaintext;
	int olen, len;
	FILE *fd_in, *fd_out;

	if (aes_init(&encrypt, &decrypt) == ERROR)
		fprintf(stderr, "ERROR: aes_init");

	olen = len = strlen(input) + 1;

	ciphertext = aes_encrypt(&encrypt, (unsigned char *)input, &len);
	plaintext = (char *)aes_decrypt(&decrypt, ciphertext, &len);

	if (strncmp(plaintext, input, olen))
		fprintf(stderr, "FAILURE: encryption/decryption failed for \"%s\"\n",
				input);
	else
		fprintf(stderr, "SUCCESS: encryption/decryption succeeded for \"%s\"\n",
				plaintext);

	free(ciphertext);
	free(plaintext);

	EVP_CIPHER_CTX_cleanup(&encrypt);
	EVP_CIPHER_CTX_cleanup(&decrypt);

	if ((fd_in = fopen("./COPYING", "r")) == NULL)
		err(1, "fopen");

	if ((fd_out = fopen("./COPYING.ciphertext", "w")) == NULL)
		err(1, "fopen");

	file_encrypt(fd_in, fd_out);

	fclose(fd_in);
	fclose(fd_out);

	if ((fd_in = fopen("./COPYING.ciphertext", "r")) == NULL)
		err(1, "fopen");

	if ((fd_out = fopen("./COPYING.plaintext", "w")) == NULL)
		err(1, "fopen");

	file_decrypt(fd_in, fd_out);

	fclose(fd_in);
	fclose(fd_out);
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
 * INTERFACE:   aes_init(EVP_CIPHER_CTX *e_ctx, EVP_CIPHER *d_ctx)
 *                  e_ctx           - OpenSSL encryption cipher structure
 *                  d_ctx           - OpenSSL decryption cipher structure
 * 
 * RETURNS:     SUCCESS or ERROR
 *
 * NOTES: Creates a 256-bit key and initializtion vector using the supplied key
 *        data. Salt may be added for taste. Fills in the encryption and
 *        decryption ctx objects.
 *----------------------------------------------------------------------------*/
int aes_init(EVP_CIPHER_CTX *e_ctx, EVP_CIPHER_CTX *d_ctx)
{
	unsigned int salt[] = {42756, 26042}; /* 8 bytes to salt the key */
	unsigned char key_data[] = {0x23, 0xf6, 0x9d, 0x75, 0xec, 0x48, 0x2d, 0xb7,
								0x57, 0x4a, 0x6f, 0xcf, 0xca, 0xd6, 0x59, 0xed,
								0x7c, 0xea, 0x84, 0xe8, 0x2c, 0x4a, 0x0b, 0xeb,
								0xc0, 0x30, 0x42, 0x5c, 0xe1, 0xeb, 0x8f, 0x0b};
	unsigned char key[KEY_SIZE];
	unsigned char iv[KEY_SIZE];
	int i, key_data_length = strlen((char *)key_data);

	/* Generate key and initialization vector (iv) for AES 256-bit CBC mode.
	 * An SHA1 digest is used to hash the supplied key materiel. AES_ROUNDS
	 * is the number of times we hash the material. More rounds are more secure
	 * but slower. */
	i = EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha1(), (unsigned char *)&salt, key_data,
			key_data_length, AES_ROUNDS, key, iv);

	if (i != 32) {
		fprintf(stderr, "Key size is %d bits and should be 256 bits.\n", i);
		return ERROR;
	}

	EVP_CIPHER_CTX_init(e_ctx);
	EVP_EncryptInit_ex(e_ctx, EVP_aes_256_cbc(), NULL, key, iv);
	EVP_CIPHER_CTX_init(d_ctx);
	EVP_DecryptInit_ex(d_ctx, EVP_aes_256_cbc(), NULL, key, iv);

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
unsigned char *aes_encrypt(EVP_CIPHER_CTX *e_ctx,
		unsigned char *plaintext, int *length)
{
	/* max ciphertext length for a n-bytes of plaintext is
	 * n + AES_BLOCK_SIZE - 1 bytes */
	int c_len = *length + AES_BLOCK_SIZE;
	int f_len = 0;
	unsigned char *ciphertext = malloc(c_len);

	/* allows reuse of 'e_ctx' for multiple encryption cycles */
	EVP_EncryptInit_ex(e_ctx, NULL, NULL, NULL, NULL);

	/* update ciphertext as c_len is filled with the length of ciphertext
	 * generated and *length is the size of plaintext in bytes */
	EVP_EncryptUpdate(e_ctx, ciphertext, &c_len, plaintext, *length);

	/* update the ciphertext with the remaining bytes */
	EVP_EncryptFinal_ex(e_ctx, ciphertext + c_len, &f_len);

	*length = c_len + f_len;

	return ciphertext;
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
unsigned char *aes_decrypt(EVP_CIPHER_CTX *e_ctx,
		unsigned char *ciphertext, int *length)
{
	/* the plaintext will always be equal to or lesser than the
	 * length of the ciphertext */
	int p_len = *length;
	int f_len = 0;
	unsigned char *plaintext = malloc(p_len);

	EVP_DecryptInit_ex(e_ctx, NULL, NULL, NULL, NULL);
	EVP_DecryptUpdate(e_ctx, plaintext, &p_len, ciphertext, *length);
	EVP_DecryptFinal_ex(e_ctx, plaintext + p_len, &f_len);

	*length = p_len + f_len;

	return plaintext;
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
 * INTERFACE:   int file_encrypt(FILE *fd_in, FILE *fd_out)
 *                  fd_in  - file to be encrypted
 *                  fd_out - destination of encrypted file
 * 
 * RETURNS:     SUCCESS or ERROR
 *
 * NOTES: Encrypts a fd_in file and saves it to fd_out.
 *----------------------------------------------------------------------------*/
int file_encrypt(FILE *fd_in, FILE *fd_out)
{
	EVP_CIPHER_CTX encrypt, decrypt;
	int read_bytes, write_bytes, file_size, aes_block;
	int file_position = 0;
	unsigned char in_buff[IN_SIZE];
	unsigned char *out_buff;
	
	if (aes_init(&encrypt, &decrypt) == ERROR)
		fprintf(stderr, "ERROR: aes_init");

	fseek(fd_in, 0, SEEK_END);
	file_size = ftell(fd_in);
	rewind(fd_in);

	while (file_position < file_size) {
		if ((read_bytes = fread(in_buff, sizeof(unsigned char), IN_SIZE, fd_in)) == ERROR)
			err(1, "fread");

		file_position += read_bytes;
		aes_block = read_bytes;

		out_buff = aes_encrypt(&encrypt, in_buff, &aes_block);

		if ((write_bytes = fwrite(out_buff, sizeof(unsigned char), aes_block, fd_out)) == ERROR)
			err(1, "fwrite");

		memset(&in_buff, 0x00, IN_SIZE);
	}

	EVP_CIPHER_CTX_cleanup(&encrypt);
	EVP_CIPHER_CTX_cleanup(&decrypt);

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
 * INTERFACE:   int file_decrypt(FILE *fd_in, FILE *fd_out)
 *                  fd_in  - file to be decrypted
 *                  fd_out - destination of decrypted file
 * 
 * RETURNS:     SUCCESS or ERROR
 *
 * NOTES: Decrypts a fd_in file and saves it to fd_out.
 *----------------------------------------------------------------------------*/
int file_decrypt(FILE *fd_in, FILE *fd_out)
{
	EVP_CIPHER_CTX encrypt, decrypt;
	int read_bytes, write_bytes, file_size, aes_block;
	int file_position = 0;
	unsigned char in_buff[OUT_SIZE];
	unsigned char *out_buff;
	
	if (aes_init(&encrypt, &decrypt) == ERROR)
		fprintf(stderr, "ERROR: aes_init");

	fseek(fd_in, 0, SEEK_END);
	file_size = ftell(fd_in);
	rewind(fd_in);

	while (file_position < file_size) {
		if ((read_bytes = fread(in_buff, sizeof(unsigned char), OUT_SIZE, fd_in)) == ERROR)
			err(1, "fread");

		file_position += read_bytes;
		aes_block = read_bytes;

		out_buff = aes_decrypt(&decrypt, in_buff, &aes_block);

		if ((write_bytes = fwrite(out_buff, sizeof(unsigned char), aes_block, fd_out)) == ERROR)
			err(1, "fwrite");

		memset(&in_buff, 0x00, IN_SIZE);
	}

	EVP_CIPHER_CTX_cleanup(&encrypt);
	EVP_CIPHER_CTX_cleanup(&decrypt);

	return SUCCESS;
}
