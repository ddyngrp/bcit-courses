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

int deflate_file(FILE *fd_in, FILE *fd_out, int level)
{
	return SUCCESS;
}

int inflate_file(FILE *fd_in, FILE *fd_out)
{
	return SUCCESS;
}

unsigned char *deflate_string(unsigned char *string, int level)
{
	return NULL;
}

unsigned char *inflate_string(unsigned char *string)
{
	return NULL;
}

void zerr(int ret)
{
}
