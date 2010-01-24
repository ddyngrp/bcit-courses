#include <stdlib.h>
#include <stdio.h>

/*== start/stop range ==*/
#define START 3  // MUST BE ODD
#define STOP 99999999

int main(void) {
	int nap;
	long num, c, i;
	long *prime;

	prime = malloc((STOP/3) * sizeof(long));

	if (!prime) {
		printf("Memory Allocation Error.");
		exit(1);
	}

	prime[0] = 2;
	prime[1] = 3;
	c = 2; /*== initial primes ==*/

	/*== only have to check odd numbers ==*/
	for (num = START; num < STOP; num += 2) {
		nap = 0;  // set not-a-prime false

		/*= cycle through list of known primes =*/
		for (i = 0; i < c; i++) { 
			/*= check if a previous prime divides evenly =*/
			/*= if so the number is not a prime =*/
			if ((num % prime[i]) == 0) {
				nap = 1;
				break;
			}

			/*= stop if prime squared is bigger than the number =*/
			if ((prime[i] * prime[i]) > num) {
				break;
			}
		}

		/*= if not-a-prime, then we found a prime =*/
		if (nap != 1) {
			/*= add prime to list of known primes =*/
			prime[c] = num;
			c++;
			printf("%d \n",num);
		}
	}

	free(prime);
}

