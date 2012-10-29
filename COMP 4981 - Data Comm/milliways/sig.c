#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/* ---- Prototypes --------------*/
void sig_handler (int);

int main (void)
{
	struct sigaction sa;
	struct sigaction oldint;

	/* Initialize the sa structure */
	sa.sa_handler = sig_handler;
	sigemptyset (&sa.sa_mask);
	sa.sa_flags = 0;

	/* Set up the signal handlers; save the old handler so we can restore it later */
	sigaction (SIGINT, &sa, &oldint);
	sigaction (SIGTSTP, &sa, NULL);

	/* Sleep for 5 seconds, or until a signal wakes it up */
	sleep (5);

	/* Restore the SIGINT */
	sigaction (SIGINT, &oldint, NULL);

	return 0;
}


/* Simple signal handler */
void sig_handler (int sig)
{
	if (sig == SIGINT)
		printf ("got SIGINT\n");
	else
		printf ("got SIGTSTP\n");
};
