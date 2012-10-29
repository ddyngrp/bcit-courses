/*-
	A. Abdulla, January 2001
*/

/*--------------- Second pipe example ---------------*/
#include <stdio.h>

#define MSGSIZE 16

char *msg1 = "Hello World #1";
char *msg2 = "Hello World #2";
char *msg3 = "Hello World #3";

int main (void)
{
  char inbuf[MSGSIZE];
  int p[2], j, pid;

  /*-- Open the pipe ----*/
  if (pipe(p) < 0)
  {
    perror("pipe call");
    exit(1);
  }
  /*-------- fork ---------------*/
  if ((pid = fork()) < 0)
  {
    perror ("fork call");
    exit(2);
  }

  /*------- parent writes information into the pipe -------*/
  if (pid > 0)
  {
    write(p[1], msg1, MSGSIZE);
    write(p[1], msg2, MSGSIZE);
    write(p[1], msg3, MSGSIZE);
    wait((int *)0);
  }

  /*------ Child reads from the pipe --------------------*/
  if (pid == 0)
  {
    for (j = 0; j < 3; j++)
    {
      read (p[0], inbuf, MSGSIZE);
      printf ("%s\n", inbuf);
    }
  }

  exit(0);
}






