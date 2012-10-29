/*-
	A. Abdulla, January 2001
*/

/*--------------- Basic pipe example ---------------*/
#include <stdio.h>

#define MSGSIZE 16

char *msg1 = "Hello World #1";
char *msg2 = "Hello World #2";
char *msg3 = "Hello World #3";

int main (void)
{
  char inbuf[MSGSIZE];
  int p[2], j;

  /*-- Open the pipe ----*/
  if (pipe(p) < 0)
  {
    perror("pipe call");
    exit(1);
  }

  /*------- write information into the pipe -------*/
  write(p[1], msg1, MSGSIZE);
  write(p[1], msg2, MSGSIZE);
  write(p[1], msg3, MSGSIZE);

  /*------ Read from the pipe --------------------*/
  for (j = 0; j < 3; j++)
  {
     read (p[0], inbuf, MSGSIZE);
     printf ("%s\n", inbuf);
  }

  exit(0);
}





