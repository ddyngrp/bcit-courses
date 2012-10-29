/*-------- Send messages using a FIFO -------------*/
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MSGSIZE   63

/*--------- globals ----------------*/
extern int  errno;
char *fifo = "fifo";

int main (int argc, char *argv[])
{
  int fd, j, nwrite;
  char msgbuf[MSGSIZE+1];

  if (argc < 2)
  {
    fprintf (stderr, "Usage: sndmsg msg ....\n");
    exit(1);
  }

  /*-- Open fifo with O_NDELAY set ----*/
  if ((fd = open (fifo, O_WRONLY|O_NDELAY)) < 0)
    perror ("fifo open failed!");
  
  /*---- Send the messages ---------------*/
  for (j = 1; j < argc; j++)
  {
    if (strlen (argv[j]) > MSGSIZE)
    {
      fprintf (stderr, "Message too long %s\n", argv[j]);
      continue;
    }
    strcpy (msgbuf, argv[j]);
    if ((nwrite = write (fd, msgbuf, MSGSIZE+1)) <= 0)
    {
      if (nwrite == 0)     /* FIFO is full */
		errno = EAGAIN;   /* fake an error */
      perror ("Message write failed!");
    }
  }
  exit(0);
}
