/*-----------------------------------------------------------------------------
 * server-multi-threaded.c
 * Copyright (C) 2010 Steffen L. Norgren <ironix@trollop.org>
 * 
 * server-multi-threaded.c is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * server-multi-threaded.c is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *----------------------------------------------------------------------------*/

#include "server-multi-threaded.h"

/*-----------------------------------------------------------------------------
 * FUNCTION:    main
 * 
 * DATE:        March 6, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   int main(int argc, char **argv)
 *                  argc - argument count
 *                  argv - array of arguments
 * 
 * RETURNS: Result on success or failure.
 * 
 * NOTES: Main entry point into the application.
 *
 *----------------------------------------------------------------------------*/
int main (int argc, const char * argv[]) {
	printf("Hello, World!\n");
	return 0;
}
