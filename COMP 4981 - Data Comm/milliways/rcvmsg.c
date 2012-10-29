/*----------- rcvmsg.c --- Receive messages via a FIFO -----*/
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MSGSIZE 63

/*-- Globals ------------*/
char *fifo = "fifo";

int main (int argc, char *argv[])
{
  int fd;
  char msgbuf[MSGSIZE+1];

  /*----- Open fifo for reading and writing ------*/
  if ((fd = open (fifo, O_RDWR)) < 0)
    perror ("fifo open failed");

  /*----- receive the messages -------*/
  for (;;)
  {
    if (read (fd, msgbuf, MSGSIZE+1) < 0)
      perror ("Message read failed!");
    /*
     * Do something interesting 
     * in real life here ...
     */

    printf ("Message Received: %s\n", msgbuf);
  }
}
