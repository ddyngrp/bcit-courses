/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE:	keycatcher.c - An application that reads keyboard input, then processes and displays
							   the results.
-- 
-- PROGRAM:		keycatcher
-- 
-- FUNCTIONS:	void catch_sig(int signo)
--				void init_buffer(char buffer[BUFFER_LEN])
--				void stty_io(int enable)
-- 				void fatal(char * s)
--
-- 
-- DATE:		January 21, 2009
-- 
-- REVISIONS:	2008-01-22 - Split into input.c, output.c, and translate.c
-- 
-- DESIGNER:	Steffen L. Norgren
-- 
-- PROGRAMMER:	Steffen L. Norgren
-- 
-- NOTES: This program will program which reads characters from a terminal keyboard, echoes the 
--		  characters to the terminal screen, process each line of characters and writes the processed 
--		  line to the screen. This program splits input, output, and translation into three processes,
--		  each of which communicate via pipes.
--
--------------------------------------------------------------------------------------------------------------------*/

#include "keycatcher.h"

pid_t c_output_pid, c_translate_pid, p_input_pid;

int main(void) {
	int p_io[2]; /* pipe for input and output */
	int p_trans[2]; /* pipe for translation output */

	/* Catch the TERM and ABRT signals */
	signal(SIGABRT, catch_sig);
	signal(SIGTERM, catch_sig);

	/* Open the pipe between input & output */
	if (pipe(p_io) < 0) {
		fatal("I/O pipe call");
	}

	/* Open the pipe between tranlation and output */
	if (pipe(p_trans) < 0) {
		fatal("Translation pipe call");
	}

	/* Fork the process */
	switch (c_output_pid = fork()) {
		case -1: /* fork creation error */
			fatal("fork call");
			break;

		case 0: /* child output process */
			output(p_io);
			break;

		default: /* parent process */
			/* For the process again */
			switch (c_translate_pid = fork()) {
				case -1: /* fork creation error */
					fatal("fork call");
					break;

				case 0: /* child translation process */
					translate(p_io, p_trans);
					break;

				default: /* parent input process */
					stty_io(0); /* Disable keyboard */
					p_input_pid = getpid();
					input(p_io, p_trans);
					break;
			}
			break;
	}

	stty_io(1); /* Enable keyboard */
	return 0;
}

/*------------------------------------------------------------------------------------------------------------------ 
-- FUNCTION:	catch_sig
-- 
-- DATE:		January 21, 2008
-- 
-- REVISIONS:	
-- 
-- DESIGNER:	Steffen L. Norgren
-- 
-- PROGRAMMER:	Steffen L. Norgren
-- 
-- INTERFACE:	void catch_sig(int signo)
					int signo: the signal that was caught
-- 
-- RETURNS: void
-- 
-- NOTES: This function should only be called when either SIGABRT or SIGTERM is caught. When called, it will
--		  determine what the signal type was and then issue that signal to all parent and child processes.
--		  
--------------------------------------------------------------------------------------------------------------------*/ 
void catch_sig(int signo) {

	/* Terminate processes */
	if (signo == 6) { /* SIGABRT */
		signal(SIGABRT, NULL);
		if (getpid() == p_input_pid) {
			printf("\r\nCATCH_ABRT: signo=%d\r\n", signo);
			stty_io(1);
		}

		kill(c_output_pid, SIGABRT);
		kill(c_translate_pid, SIGABRT);
		kill(getpid(), SIGABRT);
	}
	else if (signo == 15) { /* SIGTERM */
		signal(SIGTERM, NULL);
		if (getpid() == p_input_pid) {
			printf("\r\nCATCH_TERM: signo=%d\r\n", signo);
			stty_io(1);
		}

		kill(c_output_pid, SIGTERM);
		kill(c_translate_pid, SIGTERM);
		kill(getpid(), SIGTERM);
	}

}

/*------------------------------------------------------------------------------------------------------------------ 
-- FUNCTION:	init_buffer
-- 
-- DATE:		January 21, 2008
-- 
-- REVISIONS:	
-- 
-- DESIGNER:	Steffen L. Norgren
-- 
-- PROGRAMMER:	Steffen L. Norgren
-- 
-- INTERFACE:	void init_buffer(char buffer[BUFFER_LEN])
					char buffer[BUFFER_LEN]: the buffer array to be initialized
-- 
-- RETURNS: void
-- 
-- NOTES: This function will initialize a buffer by filling it with NULLs.
--		  
--------------------------------------------------------------------------------------------------------------------*/
void init_buffer(char buffer[BUFFER_LEN]) {
	int i;

	for (i = 0; i < BUFFER_LEN; i++) {
		buffer[i] = '\0';
	}
}

/*------------------------------------------------------------------------------------------------------------------ 
-- FUNCTION:	stty_io
-- 
-- DATE:		January 20, 2008
-- 
-- REVISIONS:	
-- 
-- DESIGNER:	Steffen L. Norgren
-- 
-- PROGRAMMER:	Steffen L. Norgren
-- 
-- INTERFACE:	void stty_io(int enable)
					int enable: set to 0 to disable normal terminal processing
								set to 1 to set the terminal set back to default
-- 
-- RETURNS: void
-- 
-- NOTES: This function will disable/enable all terminal functions in order to allow this program
--		  to take full control over keyboard input.
--		  
--------------------------------------------------------------------------------------------------------------------*/
void stty_io(int enable) {

	/* Turn on/off stty keyboard processing */
	if (enable) {
		if (system("stty -raw echo") < 0) {
			perror("enabling keyboard input");
		}
	}
	else {
		if (system("stty raw -echo") < 0) {
			perror("disabling keyboard input");
		}
	}
}

/*------------------------------------------------------------------------------------------------------------------ 
-- FUNCTION:	fatal
-- 
-- DATE:		January 20, 2008
-- 
-- REVISIONS:	
-- 
-- DESIGNER:	Steffen L. Norgren
-- 
-- PROGRAMMER:	Steffen L. Norgren
-- 
-- INTERFACE:	void fatal(char * s)
					char * s: the error string to be displayed
-- 
-- RETURNS: void
-- 
-- NOTES: This function handles all fatal errors by printing the error to stderr and then
		  issuing a SIGTERM signal to terminate the program.
--		  
--------------------------------------------------------------------------------------------------------------------*/
void fatal(char * s) {
	perror(s);

	/* Terminate processes */
	kill(getpid(), SIGTERM);
}
