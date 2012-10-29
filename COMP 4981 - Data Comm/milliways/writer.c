
/*------ Writer - handles the writing into the buffer ------------*/
#include "share.h"

/*-- Use the p() and v() defined in reader.c -----*/
extern struct sembuf p1, p2;
extern struct sembuf v1, v2;

int writer (int semid, struct databuf *buf1, struct databuf *buf2)
{
	printf ("In Writer\n");
	for (;;)
	{
		semop (semid, &p1, 1);
		semop (semid, &v2, 1);

		if (buf1->d_nread <= 0)
			return -1;

		write (1, buf1->d_buf, buf1->d_nread); /* write to stdout */
		
		semop (semid, &p1, 1);
		semop (semid, &v2, 1);

		if (buf2->d_nread <= 0)
			return -1;

		write (1, buf2->d_buf, buf2->d_nread);
	}
	return 0;
}



