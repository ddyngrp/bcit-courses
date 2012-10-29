#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
//#include <linux/ipc.h>
#include <sys/shm.h>
//#include <linux/sem.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>


#define SHMKEY1   (key_t)0x010      /*shared mem key*/
#define SHMKEY2   (key_t)0x15       /* shared mem key */
#define SEMKEY    (key_t)0x20       /* semaphore key */


/* buffer size for reads and writes */
#define SIZ       5*BUFSIZ

/* read and write count */
struct databuf
{
  int d_nread;
  char d_buf[SIZ];
};
