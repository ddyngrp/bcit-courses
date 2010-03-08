/*-----------------------------------------------------------------------------
 * linked-list.h
 * Copyright (C) 2010 Steffen L. Norgren <ironix@trollop.org>
 * 
 * linked-list.h is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * linked-list.h is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *----------------------------------------------------------------------------*/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int socket;
	char *hostname;
	int srv_req;
	int srv_data;
	int cli_req;
	int *cli_delay;
	struct node *next; /* pointer to next element in list */
} LLIST;

LLIST *list_add(LLIST **p, int i);
void list_remove(LLIST **p);
void list_clear(LLIST **p);
LLIST **list_search(LLIST **n, int i);
void list_print(LLIST *n);

#endif