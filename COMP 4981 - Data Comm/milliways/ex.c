
/* Interprocess Communication using Semaphores */

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>

/*------ Function Prototypes -----*/
int handlesem (key_t);
void P(int);
void V(int);
int initsem (key_t);

int main(int argc, char *argv[])
{
        int key, sid, status;	/* semaphore key */

	/* get semaphore id */
        key = 200;
       
	sid = initsem ((key_t)key);
	V(sid);

        /* Create child processes */
        if (fork() == 0)
       		handlesem(sid);
	if (fork() == 0)
		handlesem(sid);
	if (fork() == 0)
		handlesem(sid);
	if (fork() == 0)
		handlesem(sid);
	sleep (1);
	wait(&status);
        wait(&status);
	wait(&status);
	wait(&status);
	/* remove semaphore */
        semctl(sid,0,IPC_RMID,0);
	exit(0);
}

int handlesem (int sid)
{
  int pid = getpid();

  printf ("\nprocess %d before critical section\n", pid);
  fflush(stdout);
  P(sid);

  /*---- Critical Section -----------------*/
  printf ("\nprocess %d in critical section\n", pid);
  fflush(stdout);
  sleep (1);
  printf ("process %d leaving critical section\n", pid);
  fflush(stdout);
  /*---- End critical section ------------*/

  V(sid);

  printf ("process %d exiting\n", pid);
  fflush(stdout);
  exit(0);
}























