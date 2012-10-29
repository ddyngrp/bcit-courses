/*   Here is a sample  program  that  gets  the  canonical  name,
     aliases,  and  ``.''  separated  Internet IP addresses for a
     given destination host*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{
	int a;
         	struct hostent *hp;
         	struct in_addr addr, *addr_p;
         	char **p;

         	if (argc != 2)
	{
             		printf("Usage: %s Destination\n", argv[0]);
             		exit (1);
         	}
         	
         	addr_p = &addr;
         	if (isdigit(*argv[1]))	// Dotted IP?
         	{
         		if ((a = inet_aton(argv[1], &addr)) == 0)
         		{
             			printf("IP Address must be of the form a.b.c.d\n");
             			exit (1);
         		}

         		hp = gethostbyaddr(addr_p, sizeof (addr), PF_INET);
         		if (hp == NULL)
         		{
             			printf("host information for %s not found\n", argv[1]);
             			exit (1);
         		}
         	}
         	else
         	{
         	 	if ((hp = gethostbyname (argv[1])) == NULL) 	// Host name?
         	 	{
         	 		switch (h_errno)
         	 		{
         	 			case HOST_NOT_FOUND:
         	 				printf ("%s: No such host %s\n", argv[0], argv[1]);
         	 				exit (1);
         	 			case TRY_AGAIN:
         	 				printf ("%s: host %s try again later\n", argv[0], argv[1]);
         	 				exit (1);
         	 			case NO_RECOVERY:
         	 				printf ("%s: host %s DNS Error\n", argv[0], argv[1]);
         	 				exit (1);	
         	 			case NO_ADDRESS:
         	 				printf ("%s: No IP Address for %s\n", argv[0], argv[1]);
         	 				exit (1);
         	 			default:
         	 				printf ("Unknown Error:  %d\n", h_errno);
         	 				exit (1);
         	 		}
         	 	}
         	}	
               for (p = hp->h_addr_list; *p != 0; p++)
         	{
             		struct in_addr in;
              	char **q;

         		memcpy(&in.s_addr, *p, sizeof (in.s_addr));
         		printf("IP Address: %s\t Host Name: %s\n", inet_ntoa(in), hp->h_name);

         		for (q = hp->h_aliases; *q != 0; q++)
         			printf(" \t\t\t\t   Aliases: %s\n", *q);
          		putchar('\n');
         	}
         	exit (0);
}
