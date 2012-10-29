
/*------- Reader -------------------*/

#include "share.h"

/*-- Define the p() and v() for the two semaphores ----*/
struct sembuf p1 = {0, -1, 0}, p2 = {1, -1, 0};
struct sembuf v1 = {0, 1, 0}, v2 = {1, 1, 0};

int reader (int semid, struct databuf *buf1, struct databuf *buf2)
{
	printf ("In Reader\n");
	for (;;)
	{
		/* read into the buffer from stdin*/
		buf1->d_nread = read (0, buf1->d_buf, SIZ);

		/* Synchronization point */
		semop (semid, &v1, 1);
		semop (semid, &p2, 1);

		/*-- Test to avoid writer sleeping --*/
		if (buf1->d_nread <= 0)
			return -1;

		buf2->d_nread = read (0, buf2->d_buf, SIZ);

		semop (semid, &v1, 1);
		semop (semid, &p2, 1);

		if (buf2->d_nread <= 0)
			return -1;
	}
	return 0;
}






