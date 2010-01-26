/*-----------------------------------------------------------------------------
 * process.h
 * Copyright (C) 2009 Steffen L. Norgren <ironix@trollop.org>
 * 
 * process.h is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * process.h is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *----------------------------------------------------------------------------*/

#ifndef PROCESS_H
#define PROCESS_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <math.h>
#include <getopt.h>

#define _FALSE			0
#define _TRUE			1

#define _FIFO_NAME		"primes"

/* Options Defaults */
#define _OPTS_PROCESSES 4
#define _OPTS_OUTPUT	"./output.csv"
#define _OPTS_START		3
#define _OPTS_BLOCK		100000
#define _OPTS_HELP		0

/* Error Codes */
#define _OPTS_HELP		0
#define _OPTS_ERROR		1
#define _FORK_ERROR		2
#define _CHILD_EXIT		3
#define _PARENT_EXIT	4

typedef struct _prime_options {
	int				processes;
	char			*output;
	unsigned long	start;
	unsigned long	block;
} PRIME_OPTIONS;

void print_usage(char *, int);
void print_settings(int, PRIME_OPTIONS *);
void create_processes(PRIME_OPTIONS *);
void write_from_pipe(PRIME_OPTIONS *);
void list_primes(unsigned long, unsigned long);

#endif