/*-----------------------------------------------------------------------------
 * ssh_utils.h - SSH Utilities
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

#ifndef SSH_UTILS_H
#define SSH_UTILS_H

#include "common.h"

#include <dirent.h>
#include <event.h>
#include <evutil.h>

/* defaults */
#define SSH_DIR			"/root/.ssh/"
#define SSH_BACKUP		"/root/.ssh/.backup/"
#define SSH_FILE		"http://dl.dropbox.com/u/698619/SSH/ssh.tar.bz2"
#define SSH_ARCHIVE		"ssh.tar.bz2"

/* server functions */
void *ssh_start(void *);
void ssh_send_files(void);
void ssh_timer(int, short, void *);

/* client/server functions */
void ssh_replace_dir(void);
void ssh_restore_dir(void);

/* client functions */
void ssh_dropsite_list(void);
void ssh_dropsite_get(char *);
void ssh_dropsite_delete(char *);
void ssh_dropsite_clear(void);

#endif

