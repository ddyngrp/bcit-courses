/*
 * Assignment 1 Part 1: Assign1P1.c
 * Author: Steffen L. Norgren
 * Date: January 29, 2007
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Function Prototypes */
int randomInt(int);
void waitOnInput();

int main (void) {
	int randArray[10];
	int counter;
	int numberOfChars;
	int totalNumOfChars = 0;
		
	/* Seed the random number generator */
	srand(time(NULL));

	for(counter = 0; counter < (sizeof(randArray) / sizeof(int)); counter++) {
		randArray[counter] = randomInt(1000);
	}
	
	/* Print the header */
	printf("%s\t%s\n\n", "Value", "Total Characters");
	
	for(counter = 0; counter < (sizeof(randArray) / sizeof(int)); counter++) {
		printf("%i%n%", randArray[counter], &numberOfChars);
		totalNumOfChars += numberOfChars;
		printf("\t%d\n", totalNumOfChars);
	}
	
	waitOnInput(); /* Pause the program */
    return 0;
}

/* Returns a random integer between 1 and 1000 */
int randomInt(int maxValue) {
	int randomNum = 1 + rand() % maxValue;

	return randomNum;
}

/* Platform independent PAUSE function */
void waitOnInput() {
	printf("\nPress any key to continue . . .");
	getchar();
	//return 0;
}