/*
 * Assignment 2 Part 1: Assign2P1.c
 * Author: Steffen L. Norgren - A00683006
 * Date: February 19, 2007
 */

#include <stdio.h>
#include <stdlib.h>

/* union definition */
union integer_union {
	char c;
	short s;
	int i;
	long l;
};

/* Defining union variable */
union integer_union unionValue;

/* function prototypes */
void displayUnion();
void waitOnInput();

int main (void) {
	char *c = &unionValue.c;
	short *s = &unionValue.s;
	int *i = &unionValue.i;
	long *l = &unionValue.l;

	printf("\nPlease enter a char: ");
	scanf("%c", c);
	displayUnion();

	printf("\nPlease enter a short: ");
	scanf("%hd", s);
	displayUnion();

	printf("\nPlease enter an int: ");
	scanf("%d", i);
	displayUnion();

	printf("\nPlease enter a long: ");
	scanf("%ld", l);
	displayUnion();

	waitOnInput();
    return 0;
}

/* 
 * You mentioned this will behave differently depending
 * on the platform. Well, I use a Mac, do bear that in mind
 * when I output the results.
 */
void displayUnion() {
	printf("%-6s%s%c\n", "char", "c = ", unionValue.c);
	printf("%-6s%s%hd\n", "short", "s = ", unionValue.s);
	printf("%-6s%s%d\n", "int", "i = ", unionValue.i);
	printf("%-6s%s%ld\n", "long", "l = ", unionValue.l);
}

/* Platform independent PAUSE function */
void waitOnInput() {
	if (getchar()) {
		printf("\nPress any key to continue . . .");
		printf("%c", getchar());
	}
}