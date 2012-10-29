/*--------- showmsg.c: Show message queue details ----*/
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*--- Function prototypes -----------------*/
void mqstat_print (key_t mkey, int mqid, struct msqid_ds *mstat);

int main (int argc , char *argv[])
{
  key_t mkey;
  int msq_id;
  struct msqid_ds   msq_status;

  if (argc != 2)
  {
    fprintf (stderr, "Usage: showmsg keyval\n");
    exit(1);
  }

    /*---- Get message queue identifier ------*/
    mkey = (key_t) atoi(argv[1]);
    if ((msq_id = msgget (mkey, 0)) < 0)
    {
      perror ("msgget failed!");
      exit(2);
    }

    /*--- get status info -----------------*/
    if (msgctl (msq_id, IPC_STAT, &msq_status) < 0)
    {
      perror ("msgctl failed!");
      exit(3);
    }

    /*-- print out status information -------*/
    mqstat_print (mkey, msq_id, &msq_status);
    exit(0);
}

/*--------- status info print function ---------*/
void mqstat_print (key_t mkey, int mqid, struct msqid_ds *mstat)
{
  /*-- call the library function ctime ----*/
  char *ctime();

  printf ("\nKey %d, msg_qid %d\n\n", mkey, mqid);
  printf ("%d messages on queue\n\n", mstat->msg_qnum);
  printf ("Last send by proc %d at %s\n",
           mstat->msg_lspid, ctime(&(mstat->msg_stime)));
  printf ("Last recv by proc %d at %s\n",
           mstat->msg_lrpid, ctime(&(mstat->msg_rtime)));
}






