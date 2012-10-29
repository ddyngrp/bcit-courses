/* 
 * This is a demo program to illustrate the usage of the fork() and pipe() 
 * functions. The main process first creates pipe, then forks a child
 * process. The parent process writes messages to the pipe and the
 * child process reads them from the pipe.
 *
 * Usage: gcc -o pipe pipe.c
 *        ./pipe [<# of messages to write>] (default=3)
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MSGSIZE 16
#define NWRITE 3
#define READ 0
#define WRITE 1

void do_read(const int [], const char*);
void do_write(const int [], const int, const char*);
void fatal(const char*);
int read_arg(const int, char* []);

int main (int argc, char *argv[])
{
    int pfd[2];
    int nwrite;
    pid_t cPid, pPid;
    char psCmnd[40] = "ps -FC pipe";
    char lsofCmndP[40] = "lsof -p";
    char lsofCmndC[40] = "lsof -p";

    /* read arguments for # of messages to process */
    nwrite = read_arg(argc, argv);

    pPid = getpid();
    printf("Parent\'s PID = %d\n", pPid);

    sprintf(lsofCmndP, "%s %d %s", lsofCmndP, pPid, "| grep FIFO");

    /* create pipe */
    if ( pipe(pfd) < 0 )
    {
        fatal("pipe call");
        exit(1);
    }

    printf("\n-----------------------------------------------------------------------------\n");
    printf("Parent's pipe after pipe() (\"%s\")\n", lsofCmndP);
    system(lsofCmndP);
    printf("-------------------------------------------------------------------------------\n\n");

    printf("\n-----------------------------------------------------------------------------\n");
    printf("Processes before fork() (\"%s\")\n", psCmnd);
    system(psCmnd);
    printf("-------------------------------------------------------------------------------\n\n");

    /* create a child  */
    switch( fork() )
    {
        case -1:       /* error */ 
            fatal("fork call");
        case 0:        /* fork() returns 0 to child */
            cPid = getpid();
            printf("Child\'s PID = %d\n", cPid);
            sprintf(lsofCmndC, "%s %d %s", lsofCmndC, cPid, "| grep FIFO");
            printf("\n-----------------------------------------------------------------------------\n");
            printf("Child's pipe after fork() (\"%s\")\n", lsofCmndC);
            system(lsofCmndC);
            printf("-------------------------------------------------------------------------------\n\n");
            do_read(pfd, lsofCmndC);
            break;
        default:       /* fork() returns child's pid to parent */
            sleep(1);
            printf("\n-----------------------------------------------------------------------------\n");
            printf("Processes after fork() (\"%s\")\n", psCmnd);
            system(psCmnd);
            printf("-------------------------------------------------------------------------------\n\n");
            do_write(pfd, nwrite, lsofCmndP);
    }
}

/**/
void do_read(const int pipe[2], const char* lsofCmnd)
{
    int nread;
    char msg[MSGSIZE];
    int i = 0;

    close (pipe[WRITE]);    /* close the write descriptor */
    printf("\n-----------------------------------------------------------------------------\n");
    printf("Child's pipe after closing write descriptor (\"%s\")\n", lsofCmnd);
    system(lsofCmnd);
    printf("-------------------------------------------------------------------------------\n\n");

    while(1)
    {
        nread = read(pipe[READ], msg, MSGSIZE); 
        
        if (nread == -1)
        { 
            fatal("read call"); 
        }
        else if (nread == 0)
        {
            printf("(pipe is empty)\n");
        }
        else
        {
            msg[nread] = '\0';
            printf("Reader(child) read \"%s\"\n", msg);
            if ( strncmp(msg, "END", 3) == 0 ) break;
        }
        sleep(1);
    }
    close (pipe[READ]);    /* close the write descriptor */
    printf("Reader(child) closed the read descriptor\n");
}

/* write */
void do_write(const int pipe[2], const int nwrite, const char* lsofCmnd) 
{
    int i = 0;
    char msg[MSGSIZE];

    close(pipe[READ]);    /* close the read descriptor */
    printf("\n-----------------------------------------------------------------------------\n");
    printf("Parent's pipe after closing read descriptor (\"%s\")\n", lsofCmnd);
    system(lsofCmnd);
    printf("-------------------------------------------------------------------------------\n\n");
 
    for (; i < nwrite; i++)
    {
        sprintf(msg, "%s %d", "message", i+1);
        printf("Writer(parent) is writing \"%s\"\n", msg);
        write (pipe[WRITE], msg, MSGSIZE);
        sleep(3);
    }

    printf("Writer(parent) is writing the last message \"END\"\n");
    write (pipe[WRITE], "END", 3);

    close(pipe[WRITE]);    /* close the read descriptor */
    printf("Writer(parent) closed the write descriptor\n");
}

/* 
   reads command line parameters 
   param (in): argv - command line parameter list
   return: # of messages to write
*/ 
int read_arg(const int argc, char* argv[])
{
    char usage[128];

    sprintf(usage, "%s %s %s\n", "Usage:", argv[0], "<number of write operation>");     

    if (argc == 2)
    {
         return atoi(argv[1]);
    }

    /* TODO: error checking for argc > 2 */

    return NWRITE;
}

/* Print error msg and die */
void fatal(const char *s)
{
    perror(s);    
    exit(1);
}




