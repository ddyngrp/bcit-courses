/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE:	input.c - A child process that handles output to the terminal.
-- 
-- PROGRAM:		keycatcher
-- 
-- FUNCTIONS:	void output(int p_io[2])
--
-- 
-- DATE:		January 21, 2009
-- 
-- REVISIONS:	2008-01-22 - Split from keycatcher.c
-- 
-- DESIGNER:	Steffen L. Norgren
-- 
-- PROGRAMMER:	Steffen L. Norgren
-- 
-- NOTES: This child process waits for data to be written into the I/O pipe and echo's the data to terminal.
--
--------------------------------------------------------------------------------------------------------------------*/

#include "keycatcher.h"

/*------------------------------------------------------------------------------------------------------------------ 
-- FUNCTION:	output
-- 
-- DATE:		January 21, 2008
-- 
-- REVISIONS:	
-- 
-- DESIGNER:	Steffen L. Norgren
-- 
-- PROGRAMMER:	Steffen L. Norgren
-- 
-- INTERFACE:	void output(int p_io[2]) 
--					int p_io[2]: the input/output pipe
-- 
-- RETURNS: void
-- 
-- NOTES: Simply receives characters from 'input' or sets of characters from 'translate' and displays
--		  them on the terminal screen.
--
--------------------------------------------------------------------------------------------------------------------*/
void output(int p_io[2]) {
	int nread;
	char out_buff[BUFFER_LEN];

	close(p_io[1]); /* close the I/O write descriptor */

	/* Initialize the buffer */
	init_buffer(out_buff);

	while (1) {
		switch (nread = read(p_io[0], out_buff, BUFFER_LEN)) {
			case -1:
				fatal("output() read from I/O pipe");
				break;

			case 0:
				sleep(1);
				break;

			default:
				/* TODO: Make this work on my mac properly */
				if (write(STDOUT_FILENO, out_buff, BUFFER_LEN) < 0) {
					fatal("output() write to stdout");
				}

				/* Clear the buffer */
				init_buffer(out_buff);

				break;
		}
	}
}
