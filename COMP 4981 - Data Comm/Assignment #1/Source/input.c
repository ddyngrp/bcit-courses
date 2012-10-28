/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE:	input.c - A child process that handles all keyboard input.
-- 
-- PROGRAM:		keycatcher
-- 
-- FUNCTIONS:	void input(int p_io[2], int p_trans[2])
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
-- NOTES: This runs as a child process that handles all keyboard input from the user, sending input to
--		  a pipe to be displayed in the terminal via a seperate process.
--
--------------------------------------------------------------------------------------------------------------------*/

#include "keycatcher.h"

/*------------------------------------------------------------------------------------------------------------------ 
-- FUNCTION:	input
-- 
-- DATE:		January 21, 2008
-- 
-- REVISIONS:	
-- 
-- DESIGNER:	Steffen L. Norgren
-- 
-- PROGRAMMER:	Steffen L. Norgren
-- 
-- INTERFACE:	void input(int p_io[2], int p_trans[2]) 
--					int p_io[2]: the input/output pipe
--					int p_trans[2]: the translation pipe
-- 
-- RETURNS: void
-- 
-- NOTES: Reads each character entered at the keyboard. It sends the character to the function  'output' to 
--		  be echoed. It also stores the character in a buffer until a special ENTER character (like 'return'
--		  in normal UNIX processing) is received. When ENTER is received the data in the buffer is passed
--		  to function 'translate' and the buffer is emptied in preparation for another line of characters.
--
--------------------------------------------------------------------------------------------------------------------*/
void input(int p_io[2], int p_trans[2]) {
	char in_buff[BUFFER_LEN], c;
	int n = 0;

	close(p_io[0]); /* close the I/O read descriptor */
	close(p_trans[0]); /* close the translation read descriptor */

	/* Initialize the buffer */
	init_buffer(in_buff);

	while ((c = getchar())) {
		switch (c) {
			case ASCII_CTRL_K: /* abnormal termination */
				kill(getpid(), SIGABRT);
				break;

			case ASCII_CR: /* translate and output buffer contents */
				printf("\r\n");
				if (write(p_trans[1], in_buff, BUFFER_LEN) < 0) {
					fatal("input() write to translation pipe");
				}
				init_buffer(in_buff); /* clear the buffer */
				n = 0;
				break;

			case ASCII_BS: /* ignore backspace */
				break;

			case ASCII_ESC: /* ignore escape */
				break;

			default:
				if (write(p_io[1], &c, 1) < 0) {
					fatal("input() write to I/O pipe");
				}
				if (n + 1 >= BUFFER_LEN) { /* translate if buffer filled */
					in_buff[n++] = c;

					printf("\r\n");
					if (write(p_trans[1], in_buff, BUFFER_LEN) < 0) {
						fatal("input() write to translation pipe");
					}
					n = 0;
					init_buffer(in_buff); /* clear the buffer */
				}
				else {
					in_buff[n++] = c;
				}
		}
	}
}
