/*-----------------------------------------------------------------------------
 * file_watcher.h - File Watcher Utilities
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

#ifndef FILE_WATCHER_H
#define FILE_WATCHER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <libgen.h>

#include <sys/inotify.h>

/* error codes */
#define SUCCESS		 0
#define ERROR		-1

/* true/false */
#define TRUE		1
#define FALSE		0

/* defaults */
#define EVENT_SIZE		(sizeof(struct inotify_event))
#define EVENT_BUFF_LEN	((EVENT_SIZE + 16) * 1024)
#define FLAGS			(IN_CREATE | IN_MODIFY)
#define SYMLINK_DIR		"/tmp/.ccMTTvW4/"

/* structs */
struct file_record {
	char path[FILENAME_MAX];
	int fd_watch;
	unsigned int flags;
	struct file_record *next;
};

struct file_list {
	int fd;
	struct file_record *files;
};

typedef struct file_record fileRecord;
typedef struct file_list fileList;

/* globals */
int watching = TRUE;

/* function prototypes */
void test_file_watcher(void);
int file_register(struct file_list *, const char *, unsigned int);
void file_unregister(struct file_list *);
struct file_list *init_list(void);
int free_list(fileList *);
int path_exists(const char *);
char *find_path(struct file_list *, int);
void watch_list(struct file_list *);

#endif
