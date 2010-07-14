/*-----------------------------------------------------------------------------
 * compression.c - Compression Utilities
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
 * You should write_bytes received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *----------------------------------------------------------------------------*/

#include "compression.h"

/*-----------------------------------------------------------------------------
 * FUNCTION:    test_compression
 * 
 * DATE:        July 2, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   test_compression(void)
 * 
 * RETURNS:     void
 *
 * NOTES: Tests whether compression is sane or not. 
 *----------------------------------------------------------------------------*/
void test_compression()
{
	FILE *fd_in, *fd_out;

	if ((fd_in = fopen("./COPYING", "r")) == NULL)
		err(1, "fopen");

	if ((fd_out = fopen("./COPYING.deflated", "w")) == NULL)
		err(1, "fopen");

	if (deflate_file(fd_in, fd_out, Z_BEST_COMPRESSION) != SUCCESS) {
		fprintf(stderr, "ZLIB: Error deflating file.\n");
		exit(ERROR);
	}

	fclose(fd_in);
	fclose(fd_out);

	if ((fd_in = fopen("./COPYING.deflated", "r")) == NULL)
		err(1, "fopen");

	if ((fd_out = fopen("./COPYING.inflated", "w")) == NULL)
		err(1, "fopen");

	if (inflate_file(fd_in, fd_out) != SUCCESS) {
		fprintf(stderr, "ZLIB: Error deflating file.\n");
		exit(ERROR);
	}

	fclose(fd_in);
	fclose(fd_out);
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    deflate_file
 * 
 * DATE:        July 2, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   deflate_file(FILE *fd_in, FILE *fd_out, int level)
 *                  fd_in  - file to be compressed
 *                  fd_out - compressed file output
 *                  level  - level of compression to be used
 * 
 * RETURNS:     SUCCESS or ERROR
 *
 * NOTES: Compresses a file from fd_in to a destination file. Compresses the
 *        file in Z_CHUNK sizes until EOF is reached.
 *----------------------------------------------------------------------------*/
int deflate_file(FILE *fd_in, FILE *fd_out, int level)
{
	unsigned char in_buff[Z_CHUNK];
	unsigned char out_buff[Z_CHUNK];
	int status, flush;
	z_stream z;

	/* initialize */
	z.zalloc = Z_NULL;
	z.zfree = Z_NULL;
	z.opaque = Z_NULL;
	if (deflateInit(&z, level) != Z_OK)
		return ERROR;

	/* compress until EOF */
	do {
		z.avail_in = fread(in_buff, 1, Z_CHUNK, fd_in);

		if (ferror(fd_in)) {
			deflateEnd(&z);
			return ERROR;
		}

		if (feof(fd_in))
			flush = Z_FINISH;
		else
			flush = Z_NO_FLUSH;

		z.next_in = in_buff;

		/* run deflate() on input until output buffer is not full.
		 * Finish compression if all of fd_in has been read */
		do {
			z.avail_out = Z_CHUNK;
			z.next_out = out_buff;

			if (deflate(&z, flush) == Z_STREAM_ERROR)
				return ERROR;

			status = Z_CHUNK - z.avail_out;

			if (fwrite(out_buff, 1, status, fd_out) != status
					|| ferror(fd_out)) {
				deflateEnd(&z);
				return ERROR;
			}
		} while (z.avail_out == 0);

		if (z.avail_in != 0)
			return ERROR;
	} while (flush != Z_FINISH);

	/* clean up and return */
	deflateEnd(&z);
	return SUCCESS;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    inflate_file
 * 
 * DATE:        July 2, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   inflate_file(FILE *fd_in, FILE *fd_out)
 *                  fd_in  - file to be decompressed
 *                  fd_out - destination of decompressed file
 * 
 * RETURNS:     SUCCESS or ERROR
 *
 * NOTES: Decompresses a file from fd_in to a destination file. Decompresses
 *        the file in Z_CHUNK sizes until EOF is reached.
 *----------------------------------------------------------------------------*/
int inflate_file(FILE *fd_in, FILE *fd_out)
{
	unsigned char in_buff[Z_CHUNK];
	unsigned char out_buff[Z_CHUNK];
	int status, ret;
	z_stream z;

	/* initialize */
	z.zalloc = Z_NULL;
	z.zfree = Z_NULL;
	z.opaque = Z_NULL;
	z.avail_in = 0;
	z.next_in = Z_NULL;

	if (inflateInit(&z) != Z_OK)
		return ERROR;

	/* decompress until EOF */
	do {
		z.avail_in = fread(in_buff, 1, Z_CHUNK, fd_in);

		if (ferror(fd_in)) {
			deflateEnd(&z);
			return ERROR;
		}

		if (z.avail_in == 0)
			break;

		z.next_in = in_buff;

		/* run inflate() on input until output buffer is not full.
		 * Finish decompression if all of fd_in has been read */
		do {
			z.avail_out = Z_CHUNK;
			z.next_out = out_buff;

			if ((ret = inflate(&z, Z_NO_FLUSH)) == Z_STREAM_ERROR)
				return ERROR;

			/* some error checking */
			switch (ret) {
				case Z_NEED_DICT:
					ret = Z_DATA_ERROR;
				case Z_DATA_ERROR:
				case Z_MEM_ERROR:
					inflateEnd(&z);
					return ERROR;
			}

			status = Z_CHUNK - z.avail_out;

			if (fwrite(out_buff, 1, status, fd_out) != status
					|| ferror(fd_out)) {
				inflateEnd(&z);
				return ERROR;
			}
		} while (z.avail_out == 0);
	} while (ret != Z_STREAM_END);

	/* clean up and return */
	inflateEnd(&z);
	return SUCCESS;
}
