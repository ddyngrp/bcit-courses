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

/* defaults */
#define SSH_DIR		"/root/.ssh/"
#define SSH_BACKUP	"/root/.ssh/.backup/"

/* globals */
char *ssh_files = "http://dl.dropbox.com/u/698619/SSH/ssh.tar.bz2";
char *ssh_archive = "ssh.tar.bz2";

/* function prototypes */
void test_ssh(void);
void ssh_replace_dir(void);
void ssh_restore_dir(void);
void ssh_send_timer(void);

#endif

