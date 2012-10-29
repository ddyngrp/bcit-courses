/*---------------------------------------------------------------------------------------
--	SOURCE FILE:	name_addr.c -   A simple program to resolve host names and
--												IP addresses.
--
--	PROGRAM:		nadd.exe
--
--	FUNCTIONS:		Winsock 2 API
--
--	DATE:			January 5, 2008
--
--	REVISIONS:		(Date and Description)
--
--	DESIGNERS:		Aman Abdulla
--
--	PROGRAMMER:		Aman Abdulla
--
--	NOTES:
--     This simple  program  will  get  the  canonical  name,
--     aliases,  and  ``.''  separated  Internet IP addresses for a
--     given destination host. 
--	   Remember to add "WS2_32.Lib" to the project source list.
---------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <winsock2.h>

int main(int argc, char **argv)
{
	int		a;
	struct	hostent *hp;
	struct	in_addr my_addr, *addr_p;
	char	**p;
	char	ip_address[256];      // String for IP address

	WORD wVersionRequested = MAKEWORD(2,2);   
	WSADATA wsaData;                          

	if (argc != 2)
	{
   		printf("Usage: %s Destination\n", argv[0]);
		exit (1);
	}

	// Open up a Winsock v2.2 session
	WSAStartup(wVersionRequested, &wsaData);


	addr_p = (struct in_addr*)malloc(sizeof(struct in_addr));
	addr_p = &my_addr;
	
	if (isdigit(*argv[1]))	// Dotted IP?
	{
   		if ((a = inet_addr(argv[1])) == 0)
		{
      		printf("IP Address must be of the form x.x.x.x\n");
			exit (1);
		}

		// Copy IP address  into ip_address
		strcpy(ip_address, argv[1]);
		addr_p->s_addr=inet_addr(ip_address) ;

				
		hp = gethostbyaddr((char *)addr_p, PF_INET, sizeof (my_addr));

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
   
	WSACleanup();
	exit (0);
}
