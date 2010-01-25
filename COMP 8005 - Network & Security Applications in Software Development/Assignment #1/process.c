#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <math.h>

#define PRIME_START	3
#define PRIME_BLOCK 10000

#define PROCESSES	4
#define FIFO_NAME	"primes"

void list_primes(unsigned long long, unsigned long long);

int main (int argc, const char * argv[]) {
	unsigned long long prime_start, prime_stop;
	struct rusage ru;
	struct timeval time;
	double current_time, utime, stime;	
	pid_t pid = -2; /* force the switch into default */
	pid_t child[PROCESSES];
	int i;
	int num, fd;
	char in_buff[300], out_buff[300];
	FILE *pfile = NULL;
	char *file = "./output.csv";
	char *header = "getpid(), current_time, number, utime, stime, ru_maxrss, ru_msgsnd, ru_msgrcv, ru_nvcsw, ru_nivcsw\n";
	size_t len = 0;
	
	mknod(FIFO_NAME, S_IFIFO | 0666, 0);
		
	/* The first process's processing block. */
	prime_start = PRIME_START;
	prime_stop = prime_start + PRIME_BLOCK;
	
	for (i = 0; i <= PROCESSES; i++)
	{
		switch (pid)
		{
			case -1: /* fork error */
				perror("Error occoured with fork()\n");
				exit(99);
				
			case 0: /* child process */
				list_primes(prime_start,prime_stop);
				exit(1);
				
			default: /* parent process*/
				if (i != PROCESSES) {
					pid = fork();
					child[i] = pid;
					
					/* Subsequent process's processing blocks */
					if (pid != 0) {
						prime_start = prime_stop;
						prime_stop = prime_stop + PRIME_BLOCK;
					}
				}
		}
	}
	
	/* make sure we wait until something is written */
	usleep(10000);
	
	fd = open(FIFO_NAME, O_RDONLY);
	
	pfile = fopen(file, "w");
	if (pfile == NULL) {
		perror("Error opening file...");
	}
	
	len = strlen(header);
	fwrite(header, len, 1, pfile);
	
	do {
		if ((num = read(fd, in_buff, 300)) == -1)
			perror("read");
		else if (num > 0) {
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
			sprintf(out_buff, "%s%d, %f, 0, %f, %f, %ld, %ld, "
					"%ld, %ld, %ld\n", in_buff, getpid(),
					current_time, utime, stime, ru.ru_maxrss,
					ru.ru_msgsnd, ru.ru_msgrcv, ru.ru_nvcsw, ru.ru_nivcsw);
			
			len = strlen(out_buff);
			fwrite(out_buff, len, 1, pfile);
		}
	} while (num > 0);
	
	fclose(pfile);
	close(fd);
}

void list_primes(unsigned long long start, unsigned long long stop) {
	unsigned long long number, divisor;
	struct rusage ru;
	struct timeval time;
	double current_time, utime, stime;
	int limit, test;
	char buff[300];
    int num, fd;
	
	mknod(FIFO_NAME, S_IFIFO | 0666, 0);
	
    fd = open(FIFO_NAME, O_WRONLY);
	
	for (number = start; number < stop; number++) {
		test = 0;
		limit = sqrt(number) + 1;
		
		if (number % 2 == 0) {
			test = 1;
		}
		else {
			for (divisor = 3 ; divisor < limit && ! test; divisor += 2) {
				if (number % divisor == 0) {
					test = 1;
				}
			}
		}
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
			sprintf(buff, "%d, %f, %lld, %f, %f, %ld, %ld, "
					"%ld, %ld, %ld\n", getpid(),
					current_time, number, utime, stime, ru.ru_maxrss,
					ru.ru_msgsnd, ru.ru_msgrcv, ru.ru_nvcsw, ru.ru_nivcsw);
			
			if ((num = write(fd, buff, sizeof(buff))) == -1) {
				perror("write");
			}
		}
	}
	
	close(fd);
}