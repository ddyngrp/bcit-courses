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
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *----------------------------------------------------------------------------*/

#include "compression.h"

int main(int argc, const char * argv[])
{
	test_compression();

	return SUCCESS;
}

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
 * RETURNS:     SUCCESS or Z_MEM_ERROR, Z_STREAM_ERROR, Z_VERSION_ERROR, Z_ERRNO
 *
 * NOTES: Compresses a file from source to a destination file. Compresses the
 *        file in ZLIB_CHUNK sizes until EOF is reached.
 *----------------------------------------------------------------------------*/
int deflate_file(FILE *fd_in, FILE *fd_out, int level)
{
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
 * RETURNS:     SUCCESS or Z_MEM_ERROR, Z_STREAM_ERROR, Z_VERSION_ERROR, Z_ERRNO
 *
 * NOTES: Decompresses a file from source to a destination file. Decompresses
 *        the file in ZLIB_CHUNK sizes until EOF is reached.
 *----------------------------------------------------------------------------*/
int inflate_file(FILE *fd_in, FILE *fd_out)
{
	return SUCCESS;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    deflate_string
 * 
 * DATE:        July 2, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   unsigned char *deflate_string(unsigned char *string, int level)
 *                  string - string to be compressed
 *                  level  - level of compression to be used
 * 
 * RETURNS:     Compressed raw string bytes
 *
 * NOTES: Compresses a string and returns the raw compressed bytes.
 *----------------------------------------------------------------------------*/
unsigned char *deflate_string(unsigned char *string, int level)
{
	return NULL;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    inflate_string
 * 
 * DATE:        July 2, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   unsigned char *inflate_string(unsigned char *string)
 *                  string - string to be decompressed
 * 
 * RETURNS:     Uncompressed original string
 *
 * NOTES:  Decompresses a string and returns the original uncompressed string.
 *----------------------------------------------------------------------------*/
unsigned char *inflate_string(unsigned char *string)
{
	return NULL;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    zlib_error
 * 
 * DATE:        July 2, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   zlib_error(int ret)
 *                  ret - 
 * 
 * RETURNS:     void
 *
 * NOTES:  Reports a zlib or I/O error.
 *----------------------------------------------------------------------------*/
void zlib_error(int ret)
{
}
