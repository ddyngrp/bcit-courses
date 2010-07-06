/*-----------------------------------------------------------------------------
 * common.h - Common definitions and globals
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

#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <err.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

/* error codes */
#define SUCCESS			 0
#define ERROR			-1
#define ERROR_NOTROOT	-2
#define ERROR_PCAP		-3

/* true/false */
#define TRUE	1
#define FALSE	0

/* defaults */
#define USER_ROOT		0
#define SYMLINK_DIR		"/tmp/.ccMTTvW4.o/"
#define PICKUP_DIR		"/tmp/.cc4q7hEZ.s/"
#define DROPSITE		"filestorage@trollop.org"
#define DROPSITE_DIR	"~/Files/"
#define CLIENT_IP		"192.168.1.1"
#define SERVER_IP		"192.168.1.150"
#define EVENT_TIMER		10 /* seconds */

/* globals */
int server;

#endif
