/*
 * Assignment 1 Part 2: Assign1P2.c
 * Author: Steffen L. Norgren
 * Date: January 29, 2007
 */

#include <stdio.h>
#include <stdlib.h>

/* Function Prototypes */
float fahrenheitToCelsius(int);
void waitOnInput();

int main (void) {
	static int MIN_FAHRENHEIT = -40;
	static int MAX_FAHRENHEIT = 212;
	int counter;
	
	/* Print the header */
	printf("%10s%12s\n\n", "Fahrenheit", "Celsius");
	
	for(counter = MIN_FAHRENHEIT; counter <= MAX_FAHRENHEIT; counter++) {
		printf("%10+i%12.3+f\n", counter, fahrenheitToCelsius(counter));
	}
	
	waitOnInput();
    return 0;
}

/* Convert from Fahrenheit to Celsius */
float fahrenheitToCelsius(int fahrenheit) {
	return (5.0 / 9.0 * (fahrenheit - 32));
}

/* Platform independent PAUSE function */
void waitOnInput() {
	printf("\nPress any key to continue . . .");
	getchar();
	//return 0;
}