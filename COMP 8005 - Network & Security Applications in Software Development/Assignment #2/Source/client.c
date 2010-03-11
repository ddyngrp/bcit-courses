/*-----------------------------------------------------------------------------
 * client.c
 * Copyright (C) 2010 Steffen L. Norgren <ironix@trollop.org>
 * 
 * client.c is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * client.c is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *----------------------------------------------------------------------------*/

#include "client.h"

int server_connect(struct in_addr const *paddr, int port)
{
	int fd;
	struct sockaddr_in srv_addr;
	
	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		return ERROR_CONN_REFUSED;
	}
	
	memset(&srv_addr, 0, sizeof(srv_addr));
	memcpy(&srv_addr.sin_addr, &paddr->s_addr, 4);
	srv_addr.sin_port = htons((short int) port);
	srv_addr.sin_family = AF_INET;
	
	if (connect(fd, (struct sockaddr *) &srv_addr, sizeof(srv_addr)) == 0)
		return fd;
	
	perror("connect");
	close(fd);
	return ERROR_CONN_REFUSED;
}

int init_test(void)
{
	struct hostent *he;
	struct in_addr inadr;
	int i, k, rlen, rtotal, wlen;
	int fd = 0, connections = 1, conn_errors = 0;
	char buf[MAX_IOSIZE];
	
	/* for time in µsec */
	struct timeval tv;
	struct timezone tz;
	unsigned long start, end;
	
	/* The number of connections is 1 unless we're testing */
	if (test_vars.connect_test == TRUE)
		connections = test_vars.repeat;
	
	if (inet_aton(test_vars.server, &inadr) == 0) {
		if ((he = gethostbyname(test_vars.server)) == NULL) {
			fprintf(stderr, "unable to resolve: %s\n", test_vars.server);
			return ERROR_RESOLVE;
		}
		memcpy(&inadr.s_addr, he->h_addr_list[0], he->h_length);
	}
	
	/* begin connecting to the server */
	for (i = 0; i < connections; i++) {
		
		/* on successful connect */
		if ((fd = server_connect(&inadr, test_vars.port)) != ERROR_CONN_REFUSED) {
			if (test_vars.connect_test == TRUE) { /* run in connection test mode */
				usleep(USLEEP_TIME);
				conn_errors = 0;
			}
			else { /* run in string sending/receive mode */
				/* init server stats */
				srv_stats.requests = 0;
				srv_stats.sent_data = 0;
				srv_stats.delay = 0;

				for (k = 0; k < test_vars.repeat; k++) {
					rtotal = 0;
					
					gettimeofday(&tv, &tz);
					start = tv.tv_usec;
					
					wlen = write(fd, test_vars.string_test, test_vars.string_length);

					while (wlen != rtotal) {
						rlen = read(fd, buf, sizeof(buf));
						rtotal += rlen;
						usleep(100);
					}
					
					gettimeofday(&tv, &tz);
					end = tv.tv_usec;
					
					/* save stats */
					srv_stats.requests += 1;
					srv_stats.sent_data += wlen;
					if (start > end)
						srv_stats.delay += start - end;
					else
						srv_stats.delay += end - start;
				}
			}

		}
		else {
			if (++conn_errors == MAX_CONNECT_ERRORS)
				return ERROR_CONN_ERR;

			usleep(USLEEP_TIME);
			i--;
		}
	}

	sleep(1);
	close(fd);
	 
	return 0;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    print_usage
 * 
 * DATE:        March 5, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   void print_usage(char *command, int err)
 *                   command - the command line option used
 *                   err - error produced
 * 
 * RETURNS: void
 * 
 * NOTES: Prints out the program's useage information if the user incorrectly
 *        entered an option or used the -h or --help option.
 *
 *----------------------------------------------------------------------------*/
void print_usage(char *command, int err) {
    if (err == OPTS_HELP) {
        printf("usage: client [arguments]\n\n");
        printf("Arguments:\n");
        printf("  -t  or  --test    Run in connection test mode\n");
        printf("  -r  or  --repeat  Number of times to repeat test\n");
        printf("  -l  or  --length  Lengh of string to send\n");
        printf("  -s  or  --server  Sever to connect with\n");
        printf("  -p  or  --port    Port to connect on\n");
        printf("  -f  or  --file    Where to save statistics\n");
        printf("  -h  or  --help    Prints out this screen\n");
    }
	else if (err == OPTS_ERROR)
        printf("Try `client --help` for more information.\n");
	else {
        printf("%s: unknown error\n", command);
        printf("Try `client --help` for more information.\n");
    }
    
    exit(err);
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    print_settings
 * 
 * DATE:        March 5, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   void print_settings(int argc, PRIME_OPTIONS *opts)
 *                   argc - argument count
 * 
 * RETURNS: void
 * 
 * NOTES: Prints out the current settings that are being used in the current
 *        run of the application.
 *
 *----------------------------------------------------------------------------*/
void print_settings(int argc) {
	char *boolean;

	if (test_vars.connect_test == TRUE)
		boolean = "TRUE";
	else
		boolean = "FALSE";
	
	/* Display the current settings before running */
	if (argc == 1)
		printf("Using Default Options: (For help use \"client -h\")\n");
	else
		printf("Using the Following Options: (For help use \"client -h\")\n");	
	
	printf("  Connection testing mode:     %s\n", boolean);
	printf("  Number of times to repeat:   %d\n", test_vars.repeat);
	printf("  Lengh of string to send:     %d\n", test_vars.string_length);
	printf("  Sever to connect with:       %s\n", test_vars.server);
	printf("  Port to connect on:          %d\n", test_vars.port);
	printf("  Where to save statistics:    %s\n\n", test_vars.output_file);
}

int main(int argc, char *argv[])
{
	FILE *file;
	int i, c, retval, option_index = 0;
	char t = MIN_CHAR;
	
    static struct option long_options[] =
    {
        {"test"		, no_argument      , 0, 't'},
        {"repeat"	, required_argument, 0, 'r'},
        {"length"	, required_argument, 0, 'l'},
        {"server"	, required_argument, 0, 's'},
        {"port"		, required_argument, 0, 'p'},
        {"file"		, required_argument, 0, 'f'},
        {"help"		, no_argument      , 0, 'h'},
        {0, 0, 0, 0}
    };
	
	/* Set Defaults */
	test_vars.connect_test	= TV_TEST;
	test_vars.repeat		= TV_REPEAT;
	test_vars.string_length	= TV_LENGTH;
	test_vars.server		= TV_SERVER;
	test_vars.port			= TV_PORT;
	test_vars.output_file	= TV_FILE;
	
	while (1) {
		c = getopt_long(argc, argv, "tr:l:s:p:f:h", long_options, &option_index);
		
		if (c == -1)
			break;
		
		switch (c) {
			case 0:
				/* If the option set a flag, do nothing */
				if (long_options[option_index].flag != 0)
					break;
				break;
				
			case 't':
				test_vars.connect_test = TRUE;
				break;
				
			case 'r':
				if (atoi(optarg) > 0)
					test_vars.repeat = atoi(optarg);
				break;
				
			case 'l':
				if (atoi(optarg) > MAX_IOSIZE)
					test_vars.string_length = MAX_IOSIZE;
				else if (atoi(optarg) > 0)
					test_vars.string_length = atoi(optarg);
				break;
				
			case 's':
				test_vars.server = optarg;
				break;
				
			case 'p':
				if (atoi(optarg) > 0)
					test_vars.port = atoi(optarg);
				break;
				
			case 'f':
				test_vars.output_file = optarg;
				break;
				
			case 'h':
				print_usage(argv[0], OPTS_HELP);
				break;

			default:
				print_usage(argv[0], OPTS_ERROR);
				break;
		}
	}
	
	/* print current settings */
	print_settings(argc);
	
	/* allocate space for the test string */
	test_vars.string_test = malloc(sizeof(char) * test_vars.string_length + 1);

	/* create test string */
	for (i = 0; i < test_vars.string_length; i++) {
		if (t > MAX_CHAR)
			t = MIN_CHAR;
		else
			t++;

		test_vars.string_test[i] = t;
	}
	
	/* initiate test round */
	retval = init_test();
	
	if (retval == ERROR_RESOLVE)
		perror("fatal error");
	else if (retval == ERROR_CONN_ERR)
		perror("maximum connect errors exceeded");
	else {
		/* append stats to file */
		file = fopen(test_vars.output_file, "a");
		if (file == NULL)
			err(1, "fopen failed");
		
		if (test_vars.repeat == 0) {
			fprintf(file, "%s", "No data stored.");
		}
		
		/* printf("%lu, %lu, %lu\n", srv_stats.requests, 
			   srv_stats.sent_data, srv_stats.delay); */
		fprintf(file, "%lu, %lu, %lu\n", srv_stats.requests, 
				srv_stats.sent_data, srv_stats.delay);
		
		fclose(file);
	}


	return 0;
}
