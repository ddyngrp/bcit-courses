/********************************************************************************
* This program creates a fan of processes, where n is a command-line
* argument.
* The processes are labelled by the value of i at the time they leave the loop.
* The original process creates n-1 children. 
********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char *argv[]) 
{
	pid_t childpid = 0; 
   	int i, n;
 
   	if (argc != 2)
	{   /* check for valid number of command-line arguments */ 
      		fprintf(stderr, "Usage: %s processes\n", argv[0]);
      		return 1; 
   	}     
   	n = atoi(argv[1]);  
   	for (i = 1; i < n; i++)
      		if ((childpid = fork()) <= 0)
         		break;
 
   	fprintf(stderr, "i:%d  process ID:%ld  parent ID:%ld  child ID:%ld\n",
           i, (long)getpid(), (long)getppid(), (long)childpid);
   	return 0; 
}
