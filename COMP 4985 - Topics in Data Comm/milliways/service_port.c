/*---------------------------------------------------------------------------------------
--	SOURCE FILE:	service_port.c -   A simple program to resolve a service name to 
--												its port number. 
--
--	PROGRAM:		srvc.exe
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
--     This simple  program  will  take a user specified service name and protocol
--     and resolve it into its port number. 
--	   Remember to add "WS2_32.Lib" to the project source list.
---------------------------------------------------------------------------------------*/



#include <stdio.h>
#include <winsock2.h>

int main (int argc, char **argv)
{
	struct servent *sv;
	

	WORD wVersionRequested = MAKEWORD(2,2);   
	WSADATA wsaData;                          

	if (argc != 3)
	{
   		printf("Usage: %s <service> <Protocol>\n", argv[0]);
		exit (1);
	}

	// Open up a Winsock v2.2 session
	WSAStartup(wVersionRequested, &wsaData);

	sv = getservbyname (argv[1], argv[2]);
	if (sv == NULL)
	{
		printf ("Error in getservbyname\n");
		exit (1);
	} 
	printf ("The port number for %s is: %d\n", argv[1], ntohs(sv->s_port));
		
	WSACleanup();
	exit(0);
}
