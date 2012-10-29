
/*--------- Main routine ------------------------*/
#include "share.h"
#include <signal.h>

/*--- defines ---------*/
#define IFLAGS (IPC_CREAT|IPC_EXCL)
#define ERR ((struct databuf *) -1)


/*-------- Function prototypes ---------------*/
int getsem (void);
void getseg (struct databuf **p1, struct databuf **p2);
void remove_ipc (int);
extern int reader (int semid, struct databuf *buf1, struct databuf *buf2);
extern int writer (int semid, struct databuf *buf1, struct databuf *buf2);

/*--------- globals --------------------------*/
static int shmid1, shmid2, semid;

int main (void)
{
	int pid;
	struct databuf *buf1, *buf2;
	struct sigaction act;

	/* create and initialize the semaphore set */
	semid = getsem();

	/* create and attach shared memory segments */
	getseg (&buf1, &buf2);

	// set up the signal handler to remove the IPC objects
        act.sa_handler = remove_ipc;
        act.sa_flags = 0;
        if ((sigemptyset (&act.sa_mask) == -1 || sigaction (SIGINT, &act, NULL) == -1))
        {
                perror ("Failed to set SIGINT handler");
                exit (EXIT_FAILURE);
        }


	switch ((pid = fork()))
	{
		case -1:
			perror ("fork");
		break;
		case 0: /* child */
			writer (semid, buf1, buf2);
			//remove_ipc();
		break;
		default: /* parent */
			reader (semid, buf1, buf2);
		break;
	}
	exit(0);
}

/*------- Create and initialize the semaphore set ---------*/

int getsem (void)
{

       /*-- Initialize semaphore set --*/
	if ((semid = semget (SEMKEY, 2, 0666|IFLAGS)) < 0)
		perror ("semget");

	/*-- set the initial values ---*/
	if (semctl (semid, 0, SETVAL, 0) < 0)
		perror ("semctl1");
	if (semctl (semid, 1, SETVAL, 0) < 0)
		perror ("semctl2"); 
	return (semid);
}


/*-------- create and attach the shared memory segments ---------*/
void getseg (struct databuf **p1, struct databuf **p2)
{
        void *shmat();

	/*---- create the segments -----------------*/
	if ((shmid1 = shmget (SHMKEY1, sizeof (struct databuf), 0600|IFLAGS)) < 0)
	     perror ("shmget");
	if ((shmid2 = shmget (SHMKEY2, sizeof (struct databuf), 0600|IFLAGS)) < 0)
	     perror ("shmget");


	/*----- attach the shared memory segments ------------*/
	if ((*p1 = (struct databuf *)shmat (shmid1, 0, 0)) == ERR)
	     perror ("shmat");
	if ((*p2 = (struct databuf *)shmat (shmid2, 0, 0)) == ERR)
	     perror ("shmat");
}

/*-------- remove shared memory segments & semaphores ------------*/
void remove_ipc (int signo)
{
        if (shmctl (shmid1, IPC_RMID, (struct shmid_ds *)0) < 0)
	     perror ("shmctl");
	if (shmctl (shmid2, IPC_RMID, (struct shmid_ds *)0) < 0)
	     perror ("shmctl");
	if (semctl (semid, 0, IPC_RMID, 0) < 0)
	     perror ("semctl");
}
