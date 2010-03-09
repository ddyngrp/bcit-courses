/*-----------------------------------------------------------------------------
 * linked-list.c
 * Copyright (C) 2010 Steffen L. Norgren <ironix@trollop.org>
 * 
 * linked-list.c is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * linked-list.c is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *----------------------------------------------------------------------------*/

#include "linked-list.h"

LLIST *list_add(LLIST **p, int cli_port)
{
	LLIST *n;
	
	if (p == NULL)
		return NULL;
	
	n = malloc(sizeof(LLIST));
	if (n == NULL)
		return NULL;
	
	n->next = *p; /* the previous element (*p) now becomes the "next" element */
	*p = n;       /* add new empty element to the front (head) of the list */
	n->cli_port = cli_port;
	
	return *p;
}

void list_remove(LLIST **p) /* remove head */
{
	if (p != NULL && *p != NULL) {
		LLIST *n = *p;
		*p = (*p)->next;
		free(n);
	}
}

void list_clear(LLIST **p) /* remove all */
{
	while (*p != NULL) {
		LLIST *n = *p;
		*p = (*p)->next;
		free(n);
	}
}

void list_print(LLIST *n)
{
	if (n == NULL) {
		printf("list is empty\n");
	}
	while (n != NULL) {
		printf("%s, %d, %d\n", n->cli_addr, n->cli_port, n->srv_data);
		n = n->next;
	}
}

void list_write(LLIST *n, char *fileName)
{
	FILE *file;
	
	file = fopen(fileName, "w");
	if (file == NULL)
		err(1, "fopen failed");
	
	if (n == NULL) {
		fprintf(file, "%s", "No data stored.");
	}
	while (n != NULL) {
		fprintf(file, "%s, %d, %d\n", n->cli_addr, n->cli_port, n->srv_data);
		n = n->next;
	}
}