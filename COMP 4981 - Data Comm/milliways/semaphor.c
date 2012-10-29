#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>

void P(int sid)     /* acquire semophore */
{
    struct sembuf *sembuf_ptr;
        
	sembuf_ptr= (struct sembuf *) malloc (sizeof (struct sembuf *) );
    sembuf_ptr->sem_num = 0;
    sembuf_ptr->sem_op = -1;
    sembuf_ptr->sem_flg = SEM_UNDO;

    if ((semop(sid,sembuf_ptr,1)) == -1)
		printf("semop error\n");
}

void V(int sid)     /* release semaphore */
{
	struct sembuf *sembuf_ptr;
        
	sembuf_ptr= (struct sembuf *) malloc (sizeof (struct sembuf *) );
    sembuf_ptr->sem_num = 0;
    sembuf_ptr->sem_op = 1;
    sembuf_ptr->sem_flg = SEM_UNDO;

    if ((semop(sid,sembuf_ptr,1)) == -1)
		printf("semop error\n");
}

