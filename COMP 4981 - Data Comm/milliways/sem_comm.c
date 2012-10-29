/* Interprocess Communication using Semaphores */

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>

/*---- function prototypes ----*/
int cleanup (void);

/*--- globals -------*/
int sid;

int main(int argc, char *argv[])
{
	int i, j, status, number_of_communications;
    int key;	/* semaphore key */
	extern cleanup();

    if (argc < 2)
    {
		printf("Bad arg count\n");
        printf("Usage: %s number_of_communications\n", argv[0]);
        exit(1);
    }

    /* remove semaphore if an interrupt occurs */
    for (i=0; i<20; i++)
		signal(i,cleanup);

    number_of_communications = atoi(argv[1]);

    /* get semaphore id */
    key = 100;
    if ((sid = semget((key_t)key,1,0666|IPC_CREAT)) == -1)
		printf("semget error\n");
    V(sid);

    /* Create child process */
    if (fork() == 0)
    {
		for(i=0; i<number_of_communications; i++)
        {
			/* Race to execute critical section */
            fflush(stdout);
            P(sid);

            for(j=0; j<10; j++) 
				printf("In child's critical section\n");

            V(sid);
         }
         exit(0);
	}

    for(i=0; i<number_of_communications; i++)
    {
		fflush(stdout);
        P(sid);

        for(j=0; j<10; j++) 
			printf("critical section of parent\n");

        V(sid);
	}
    wait(&status);
    /* remove semaphore */
    semctl(sid,0,IPC_RMID,0);
	exit(0);
}

int cleanup(void)
{
	semctl(sid,1,IPC_RMID,0);
    exit(1);
}












