/*-----------------------------------------------------------------------------
 * process.c
 * Copyright (C) 2009 Steffen L. Norgren <ironix@trollop.org>
 * 
 * process.c is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * process.c is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *----------------------------------------------------------------------------*/

#include "process.h"

/*-----------------------------------------------------------------------------
 * FUNCTION:    main
 * 
 * DATE:        January 25, 2010
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
 * RETURNS: Result on success or failure.
 * 
 * NOTES: Main entry point into the application. Parses command line options
 *        and sets up conditions to create new child processes.
 *
 *----------------------------------------------------------------------------*/
int main (int argc, char **argv) {
	PRIME_OPTIONS *opts;
	int c, option_index = 0;
	
    static struct option long_options[] =
    {
        {"processes"			, required_argument	, 0, 'p'},
        {"output"				, required_argument	, 0, 'o'},
        {"start"				, required_argument	, 0, 's'},
        {"block"				, required_argument	, 0, 'b'},
        {"help"					, no_argument		, 0, 'h'},
        {0, 0, 0, 0}
    };
	
	opts = malloc(sizeof(PRIME_OPTIONS));

	/* Set Defaults */
	opts->output = _OPTS_OUTPUT;
	opts->processes = _OPTS_PROCESSES;
	opts->start = _OPTS_START;
	opts->block = _OPTS_BLOCK;
	
	while (1) {
		c = getopt_long(argc, argv, "p:o:s:b:h", long_options, &option_index);
		
		if (c == -1)
			break;

		switch (c) {
			case 0:
				/* If the option set a flag, do nothing */
				if (long_options[option_index].flag != 0)
					break;
				break;
				
			case 'p':
				if (atoi(optarg) > 0)
					opts->processes = atoi(optarg);
				break;
			
			case 'o':
				opts->output = optarg;
				break;
				
			case 's':
				if (atoi(optarg) > 0)
					opts->start = atoi(optarg);
				break;
				
			case 'b':
				if (atoi(optarg) > 0)
					opts->block = atoi(optarg);
				break;
				
			case 'h':
				print_usage(argv[0], _OPTS_HELP);
				break;
				
			default:
				print_usage(argv[0], _OPTS_ERROR);
				break;
		}
	}
	
	/* Print current settings */
	print_settings(argc, opts);
	
	/* Start the child processes */
	create_processes(opts);
	
	/* Start reading from the pipe and writing to the file */
	printf("Parent pid %d writing output to file %s\n", getpid(), opts->output);
	write_from_pipe(opts);
	printf("Parent pid %d finished writing to file %s\n", getpid(), opts->output);
	
	free(opts);
	exit(_PARENT_EXIT);
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    print_usage
 * 
 * DATE:        January 25, 2010
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
    if (err == _OPTS_HELP) {
        printf("usage: process [arguments]\n\n");
        printf("Arguments:\n");
        printf("  -p  or  --processes  Number of processes to use\n");
        printf("  -o  or  --output     Output to file name\n");
        printf("  -s  or  --start      Start prime list from\n");
        printf("  -b  or  --block      Size of block for each process\n");
        printf("  -h  or  --help       Prints out this screen\n");
    }
	else if (err == _OPTS_ERROR)
        printf("Try `process --help` for more information.\n");
	else {
        printf("%s: unknown error\n", command);
        printf("Try `process --help` for more information.\n");
    }
    
    exit(err);
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    print_settings
 * 
 * DATE:        January 25, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   void print_settings(int argc, PRIME_OPTIONS *opts)
 *                   argc - argument count
 *                   opts - structure that sores options
 * 
 * RETURNS: void
 * 
 * NOTES: Prints out the current settings that are being used in the current
 *        run of the application.
 *
 *----------------------------------------------------------------------------*/
void print_settings(int argc, PRIME_OPTIONS *opts) {
	/* Display the current settings before running */
	if (argc == 1)
		printf("Using Default Options: (For help use \"process -h\")\n");
	else
		printf("Using the Following Options: (For help use \"process -h\")\n");
	
	printf("  Number of Child Processes:   %d\n", opts->processes);
	printf("  Output to File:              %s\n", opts->output);
	printf("  Start Listing Primes From:   %ld\n", opts->start);
	printf("  Block Size for each Process: %ld\n\n", opts->block);
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    create_processes
 * 
 * DATE:        January 25, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   void create_threads(PRIME_OPTIONS *opts)
 *                   opts - structure that sores options
 * 
 * RETURNS: void
 * 
 * NOTES: Creates a specified number of processes, which is defined by the
 *        opts->processes variable.
 *
 *----------------------------------------------------------------------------*/
void create_processes(PRIME_OPTIONS *opts) {
	unsigned long prime_start, prime_stop;
	pid_t pid = -2; /* force the switch into default */
	pid_t *child;
	int i;
	
	child = malloc(opts->processes * sizeof(pid_t));

	/* The first process's processing block. */
	prime_start = opts->start;
	prime_stop = opts->start + opts->block;
	
	for (i = 0; i <= opts->processes; i++)
	{
		switch (pid)
		{
			case -1: /* fork error */
				perror("Error occoured with fork()\n");
				exit(_FORK_ERROR);
				
			case 0: /* child process */
				printf("Child pid %d starting on range %ld - %ld\n",
					   getpid(), prime_start, prime_stop);
				
				list_primes(prime_start,prime_stop);
				
				printf("Child pid %d finished range %ld - %ld\n",
					   getpid(), prime_start, prime_stop);
				
				exit(_CHILD_EXIT);
				
			default: /* parent process*/
				if (i != opts->processes) {
					pid = fork();
					child[i] = pid;
					
					/* Subsequent process's processing blocks */
					if (pid != 0) {
						prime_start = prime_stop;
						prime_stop = prime_stop + opts->block;
					}
				}
		}
	}	
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    write_from_pipe
 * 
 * DATE:        January 25, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   void write_from_pipe(PRIME_OPTIONS *opts)
 *                   opts - structure that sores options
 * 
 * RETURNS: void
 * 
 * NOTES: Reads from the named pipe as long as data exists. Once data is read
 *        from the named pipe, it is immediately written to disk along with
 *        usage information for the parent process.
 *
 *----------------------------------------------------------------------------*/
void write_from_pipe(PRIME_OPTIONS *opts) {
	struct rusage ru;
	struct timeval time;
	double current_time, utime, stime;	
	FILE *pfile = NULL;
	size_t len = 0;
	int num, fd;
	char in_buff[300], out_buff[300];
	char *header = "getpid(), current_time, number, utime, stime, ru_maxrss, "
				   "ru_msgsnd, ru_msgrcv, ru_nvcsw, ru_nivcsw\n";
	unsigned long count = 0;
	
	/* make sure we wait until something is written */
	usleep(10000);
	
	mknod(_FIFO_NAME, S_IFIFO | 0666, 0); /* Create the fifo */
	fd = open(_FIFO_NAME, O_RDONLY);
	
	pfile = fopen(opts->output, "w");
	if (pfile == NULL)
		perror("Error opening file...");
	
	len = strlen(header);
	fwrite(header, len, 1, pfile);
	
	do {
		if ((num = read(fd, in_buff, 300)) == -1)
			perror("read");
		else if (num > 0) {
			sprintf(out_buff, "%s", in_buff);
			
			len = strlen(out_buff);
			fwrite(out_buff, len, 1, pfile);
			count++;
			
			/* Add parent info after each process has reported */
			if (count % opts->processes == 0) {
				getrusage(RUSAGE_SELF, &ru);
				gettimeofday(&time, NULL);
				current_time = (double)(time.tv_sec * 1000000 + time.tv_usec)/1000000.0;
				utime = (double)ru.ru_utime.tv_sec + (double)ru.ru_utime.tv_usec / 1000000.0;
				stime = (double)ru.ru_stime.tv_sec + (double)ru.ru_stime.tv_usec / 1000000.0;
				
				/* Output Structure
				 * Process ID:						getpid()
				 * Time of Day:						current_time
				 * Padding for Excel:				0
				 * User Time Used:					utime
				 * System Time Used:				stime
				 * Max Resident Memory Size:		ru.ru_maxrss
				 * Messages Sent:					ru.ru_msgsnd
				 * Messages Received:				ru.ru_msgrcv
				 * Voluntary Context Switches:		ru.ru_nvcsw
				 * Involuntary Context Switches:	ru.ru_nivcsw
				 */
				sprintf(out_buff, "%d, %f, 0, %f, %f, %ld, %ld, "
						"%ld, %ld, %ld\n", getpid(),
						current_time, utime, stime, ru.ru_maxrss,
						ru.ru_msgsnd, ru.ru_msgrcv, ru.ru_nvcsw, ru.ru_nivcsw);
				
				len = strlen(out_buff);
				fwrite(out_buff, len, 1, pfile);
			}
		}
	} while (num > 0);
	
	fclose(pfile);
	close(fd);
	unlink(_FIFO_NAME);
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    list_primes
 * 
 * DATE:        January 25, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   void list_primes(unsigned long start, unsigned long stop)
 *                   start - where to begin searching for primes
 *                   stop - where to stop searching for primes
 * 
 * RETURNS: void
 * 
 * NOTES: Calculates prime numbers within a given range. Once a prime number is
 *        found, the result is written to the named pipe for the parent process
 *        to read. Additional information regarding system time and memory usage
 *        is also sent through the pile to enable further analysis.
 *
 *----------------------------------------------------------------------------*/
void list_primes(unsigned long start, unsigned long stop) {
	unsigned long number, divisor;
	struct rusage ru;
	struct timeval time;
	double current_time, utime, stime;
	int limit, test, num, fd;
	char buff[300];
	
	mknod(_FIFO_NAME, S_IFIFO | 0666, 0); /* Create the fifo */
    fd = open(_FIFO_NAME, O_WRONLY);
	
	for (number = start; number < stop; number++) {
		test = 0;
		limit = sqrt(number) + 1;
		
		if (number % 2 == 0)
			test = 1;
		else
			for (divisor = 3 ; divisor < limit && ! test; divisor += 2)
				if (number % divisor == 0)
					test = 1;
		if (!test) {
			getrusage(RUSAGE_SELF, &ru);
			gettimeofday(&time, NULL);
			current_time = (double)(time.tv_sec * 1000000 + time.tv_usec)/1000000.0;
			utime = (double)ru.ru_utime.tv_sec + (double)ru.ru_utime.tv_usec / 1000000.0;
			stime = (double)ru.ru_stime.tv_sec + (double)ru.ru_stime.tv_usec / 1000000.0;
			
			/* Output Structure
			 * Process ID:						getpid()
			 * Time of Day:						current_time
			 * Prime Number:					number
			 * User Time Used:					utime
			 * System Time Used:				stime
			 * Max Resident Memory Size:		ru.ru_maxrss
			 * Messages Sent:					ru.ru_msgsnd
			 * Messages Received:				ru.ru_msgrcv
			 * Voluntary Context Switches:		ru.ru_nvcsw
			 * Involuntary Context Switches:	ru.ru_nivcsw
			 */
			sprintf(buff, "%d, %f, %ld, %f, %f, %ld, %ld, "
					"%ld, %ld, %ld\n", getpid(),
					current_time, number, utime, stime, ru.ru_maxrss,
					ru.ru_msgsnd, ru.ru_msgrcv, ru.ru_nvcsw, ru.ru_nivcsw);
			
			if ((num = write(fd, buff, sizeof(buff))) == -1)
				perror("write");
		}
	}
	
	close(fd);
}