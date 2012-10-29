/* sigex -- Simple signal demo --------------*/

#include <stdio.h>
#include <signal.h>


/*----------- Function Prototypes --------------------*/
int catch_int (int);    /* The function associated with SIGINT */

int main(void)
{
  /*---------- Before signal call SIGINT will terminate process (default) */

  signal (SIGINT, catch_int);

  /*- After signal call control is passed to catchint when SIGINT is received*/

  printf ("Sleep call #1\n");
  sleep(1);
  printf ("Sleep call #2\n");
  sleep(1);
  printf ("Sleep call #3\n");
  sleep(1);
  printf ("Sleep call #4\n");
  sleep(1);

  printf ("Exiting\n");
  exit(0);


}

/*---- Simple function which handles SIGINT -----*/
int catch_int (int signo)
{
  printf ("\nCATCH_INT: signo=%d\n", signo);
  printf ("CATCH_INT: Returning\n\n");
}
