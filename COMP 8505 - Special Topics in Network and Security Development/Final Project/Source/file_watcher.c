/*-----------------------------------------------------------------------------
 * file_watcher.c - File Watcher Utilities
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

#include "file_watcher.h"

void *file_watcher(void *ptr)
{
	char command[FILENAME_MAX];

	list = init_list();

	/* create pickup directory */
	memset(command, 0x00, FILENAME_MAX);
	sprintf(command, "mkdir %s > /dev/null 2>&1", PICKUP_DIR);

	if(system(command) == ERROR)
		err(1, "system");

	/* create storage directory */
	memset(command, 0x00, FILENAME_MAX);
	sprintf(command, "mkdir %s > /dev/null 2>&1", SYMLINK_DIR);

	if(system(command) == ERROR)
		err(1, "system");

	if (list == NULL) {
		fprintf(stderr, "list is NULL\n");
		return NULL;
	}

	while (watching) {
		watch_list(list);
	}

	/* delete pickup directory */
	memset(command, 0x00, FILENAME_MAX);
	sprintf(command, "rm -rf %s > /dev/null 2>&1", PICKUP_DIR);

	if(system(command) == ERROR)
		err(1, "system");

	/* delete storage directory */
	memset(command, 0x00, FILENAME_MAX);
	sprintf(command, "rm -rf %s > /dev/null 2>&1", SYMLINK_DIR);

	if(system(command) == ERROR)
		err(1, "system");

	return NULL;
}

int file_register(struct file_list *list, const char *path, unsigned int flags)
{
	fileRecord *fr = (fileRecord *)malloc(sizeof(fileRecord));
	int length = strlen(path) + 1;

	memset(fr->path, 0x00, FILENAME_MAX);
	strncpy(fr->path, path, length);

	fr->flags = flags;
	fr->next = list->files;
	fr->fd_watch =  inotify_add_watch(list->fd, path, flags);

	if (fr->fd_watch == 0) {
		free(fr);
		err(1, "inotify_add_watch");
		return ERROR;
	}

	list->files = fr;

	return SUCCESS;
}

void file_unregister(struct file_list *list)
{
	fileRecord *fr_next, *fr_current;

	if (list->files == NULL) {
		fprintf(stderr, "list->files is NULL\n");
		return;
	}

	fr_current = list->files;

	if (list->files->next != NULL)
		fr_next = list->files->next;
	else
		fr_next = NULL;

	if (inotify_rm_watch(list->fd, fr_current->fd_watch) < 0) {
		err(1, "inofity_rm_watch");
		return;
	}

	list->files = fr_next;

	free(fr_current);
}

struct file_list *init_list(void)
{
	int fd = inotify_init();
	fileList *list;

	if (fd < SUCCESS)
		err(1, "inotify_init");

	list = (fileList *)malloc(sizeof(fileList));
	list->fd = fd;
	list->files = NULL;

	return list;
}

int free_list(fileList *list)
{
	if (list == NULL) {
		fprintf(stderr, "list is null\n");
		return ERROR;
	}

	while (list->files != NULL)
		file_unregister(list);

	free(list);
	return SUCCESS;
}

int path_exists(const char *path)
{
	struct stat buffer;

	return (stat(path, &buffer) == 0 || errno != ENOENT);
}

char *find_path(struct file_list *list, int fd_watch)
{
	fileRecord *fr = list->files;
	char *file_name = (char *)malloc(FILENAME_MAX);

	memset(file_name, 0x00, FILENAME_MAX);

	while (fr != NULL) {
		if (fr->fd_watch == fd_watch) {
			strncpy(file_name, fr->path, FILENAME_MAX - 1);
			break;
		}

		fr = fr->next;
	}

	if (strlen(file_name) > 0)
		return file_name;

	return NULL;
}

void watch_list(struct file_list *list)
{
	ssize_t len, i = 0;
	int buffer[EVENT_BUFF_LEN] = {0};

	len = read(list->fd, buffer, EVENT_BUFF_LEN - 1);

	while (i < len) {
		struct inotify_event *event = (struct inotify_event *)&buffer[i];
		char command[FILENAME_MAX];

		memset(command, 0x00, FILENAME_MAX);

		if (event->mask & IN_CREATE || event->mask & IN_MODIFY) {
			sprintf(command, "ln -sf %s%s %s > /dev/null 2>&1",
					find_path(list, event->wd), event->name, SYMLINK_DIR);

			if (system(command) == ERROR)
				err(1, "system");
		}

		i += sizeof(struct inotify_event) + event->len;
	}
}
