
/* Semaphore creation and initialization function */

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include <errno.h>

extern int errno;



int initsem (key_t key)
{
  int sid, status=0;

  if ((sid = semget((key_t)key, 1, 0666|IPC_CREAT|IPC_EXCL)) == -1)
  {
    if (errno == EEXIST)
      sid = semget ((key_t)key, 1, 0);
  }
  else   /* if created */
      status = semctl (sid, 0, SETVAL, 1);
  if ((sid == -1) || status == -1)
  {
    perror ("initsem failed\n");
    return (-1);
  }
  else
    return (sid);
}



