/*-
	A. Abdulla, January 2001
*/

/*--------------- Third pipe example using O_NDELAY ---------------*/
#include <stdio.h>
#include <fcntl.h>

#define MSGSIZE 16

/*------ Function prototypes ----------*/
void parent (int p[]);
void child (int p[]);
void fatal (char *);

/*------- Message Strings -------------*/
char *msg1 = "Hello World";
char *msg2 = "Goodbye World";

int main (void)
{
  int pfd[2];

  /*----- Open the pipe -----------*/
  if (pipe(pfd) < 0)
    fatal ("pipe call");

  /*---- Set the O_NDELAY flag for p[0] -----------*/
  if (fcntl (pfd[0], F_SETFL, O_NDELAY) < 0)
    fatal ("fcntl call");

  /*-------- fork ---------------*/

  switch(fork())
  {
    case -1:        /* error */
      fatal ("fork call");
    case 0:        /* It's the child */
      child (pfd);
    default:       /* parent */
      parent (pfd);
  }
}

/*------- Parent Code -------*/
void parent (int p[2])
{
  int nread;
  char buf[MSGSIZE];

  close (p[1]);    /* close the write descriptor */

  for (;;)
  {
    switch (nread = read(p[0], buf, MSGSIZE))
    {
      case -1:
      case 0:
	    printf ("(pipe empty)\n");
	    sleep(1);
        break;
      default:
        if (strcmp (buf, msg2) == 0)
        {
	      printf ("End of Conversation\n");
	      exit(0);
        }
        else
	      printf ("MSG = %s\n", buf);
    }
  }
}

/*------ Child Code --------------------*/
void child (int p[2])
{
  int count;

  close (p[0]);    /* close the read descriptor */

  for (count = 0; count < 3; count ++)
  {
    write (p[1], msg1, MSGSIZE);
    sleep (3);
  }
  /*--- Send final message ------------*/
  write (p[1], msg2, MSGSIZE);
  exit(0);
}

/*---------- Error function ------*/
void fatal (char *s)
{
  perror (s);    /* print error msg and die */
  exit(1);
}




