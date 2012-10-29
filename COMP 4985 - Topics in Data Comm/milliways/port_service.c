/*---------------------------------------------------------------------------------------
--	SOURCE FILE:	port_service.c -   A simple program to resolve a port number to 
--												its service name. 
--
--	PROGRAM:		prts.exe
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
--     This simple  program  will  take a user specified port number nd protocol
--     and resolve it into its service name. 
--	   Remember to add "WS2_32.Lib" to the project source list.
---------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <winsock2.h>

int main(int argc, char **argv)
{
	struct servent *sv;
	int s_port;
	
	WORD wVersionRequested = MAKEWORD(2,2);   
	WSADATA wsaData;                          

	if (argc != 3)
	{
   		printf("Usage: %s <Port> <Protocol>\n", argv[0]);
		exit (1);
	}

	// Open up a Winsock v2.2 session
	WSAStartup(wVersionRequested, &wsaData);

	s_port = atoi(argv[1]);
		
	sv = getservbyport (htons(s_port), argv[2]);
	if (sv == NULL)
	{
		printf ("Error in getservbyport\n");
		exit (1);
	} 
		printf ("The service for %s port %d is: %s\n", argv[2], s_port, sv->s_name);

	WSACleanup();
	exit (0);
}
