/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE:	translate.c - A child process that handles translation of user input
-- 
-- PROGRAM:		keycatcher
-- 
-- FUNCTIONS:	void translate(int p_io[2], int p_trans[2])
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
-- NOTES: This child process waits for data to be written into the translation pipe and then modifies the
--		  data before sending it to the output function.
--
--------------------------------------------------------------------------------------------------------------------*/

#include "keycatcher.h"

/*------------------------------------------------------------------------------------------------------------------ 
-- FUNCTION:	translate
-- 
-- DATE:		January 21, 2008
-- 
-- REVISIONS:	
-- 
-- DESIGNER:	Steffen L. Norgren
-- 
-- PROGRAMMER:	Steffen L. Norgren
-- 
-- INTERFACE:	void translate(int p_io[2], int p_trans[2]) 
--					int p_io[2]: the input/output pipe
--					int p_trans[2]: the translation pipe
-- 
-- RETURNS: void
-- 
-- NOTES: Processes the characters passed to it. It performs the normal UNIX erase and line-kill processing
--		  and also translates all occurrences of the character “a” to “z”. After completing the processing it
--		  sends the new line of characters to the function 'output'.
--
--------------------------------------------------------------------------------------------------------------------*/
void translate(int p_io[2], int p_trans[2]) {
	int nread, i, k, term_sig = 0;
	char trans_in_buff[BUFFER_LEN];
	char trans_out_buff[BUFFER_LEN];

	close(p_io[0]); /* close the I/O read descriptor */
	close(p_trans[1]); /* close the translation write descriptor */

	/* Initialize the buffer */
	init_buffer(trans_in_buff);
	init_buffer(trans_out_buff);

	while (1) {
		switch (nread = read(p_trans[0], trans_in_buff, BUFFER_LEN)) {
			case -1:
				fatal("translate() read from I/O pipe");
				break;

			case 0:
				sleep(1);
				break;

			default:
				k = 0;

				for (i = 0; i < BUFFER_LEN; i++) {
					if (trans_in_buff[i] == 'a') { /* Changes 'a' to 'z' */
						trans_out_buff[i - k] = 'z';
					}
					else if (trans_in_buff[i] == 'X') { /* Deletes previous char */
						if (i - (k + 1) >= 0) {
							k += 2;
						}
					}
					else if (trans_in_buff[i] == 'K') { /* Clears the line */
						k = i + 1;
					}
					else if (trans_in_buff[i] == 'T') { /* Causes program termination */
						term_sig = 1; /* terminate after the line is displayed */
					}
					else { /* No processing needed */
						trans_out_buff[i - k] = trans_in_buff[i];
					}
				}

				if (write(p_io[1], trans_out_buff, BUFFER_LEN) < 0) {
					fatal("translate() write to I/O pipe");
				}

				/* Output a new line */
				if (write(p_io[1], "\r\n", 2) < 0) {
					fatal("translate() write to I/O pipe");
				}

				/* Clear the buffer */
				init_buffer(trans_in_buff);
				init_buffer(trans_out_buff);

				/* Terminate processes */
				if (term_sig) {
					kill(getpid(), SIGTERM);
				}
				break;
		}
	}
}