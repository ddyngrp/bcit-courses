/*---------------------------------------------------------------------------------------
--	SOURCE FILE:	wsTools.c -   Handles all Winsock requests for the program.
--
--	PROGRAM:		winsock_tool.exe
--
--	FUNCTIONS:		
--
--
--	DATE:			January 26, 2009
--
--	REVISIONS:		
--
--	DESIGNERS:		Steffen L. Norgren
--
--	PROGRAMMER:		Steffen L. Norgren
--
--	NOTES:	Handles all Winsock requests for the program, such as host name lookup,
--			IP address lookup, service lookup, port lookup, etc.
--			Remember to add "WS2_32.Lib" to the project source list.
---------------------------------------------------------------------------------------*/

#include <winsock2.h>
#include "winMain.h"
#include "wsTools.h"

/*--------------------------------------------------------------------------------------- 
--	FUNCTION:	ws_name_addr
-- 
--	DATE:		January 26, 2009
-- 
--	REVISIONS:	
-- 
--	DESIGNER:	Steffen L. Norgren
-- 
--	PROGRAMMER:	Steffen L. Norgren
-- 
--	INTERFACE:	ws_name_addr(char * host_name)
--					char * host_name:	A host name string
-- 
--	RETURNS:	void
-- 
--	NOTES:	Gets the canonical name associated with an internet IP address and
--			outputs the results.
--
---------------------------------------------------------------------------------------*/
void ws_name_addr(char * host_name) {
	struct	hostent *hp;
	char	**p;
	LPSTR	psBuff;

	WORD wVersionRequested = MAKEWORD(2,2);
	WSADATA wsaData;

	psBuff = (LPSTR)VirtualAlloc((LPVOID)NULL, (DWORD)(255),
					MEM_COMMIT, PAGE_READWRITE);

	WSAStartup(wVersionRequested, &wsaData);

	OutputText((LPCTSTR)"\n");
	OutputText((LPCTSTR)"================ Host Name Lookup ================\n");
	if (!isdigit(*host_name)) { // must not be an IP address
		if ((hp = gethostbyname(host_name)) == NULL) { // Host name?
			switch(h_errno) {
				case HOST_NOT_FOUND:
					wsprintf(psBuff, (LPCTSTR)"No such host %s\n", host_name);
					OutputText(psBuff);
					break;

				case TRY_AGAIN:
					wsprintf(psBuff, (LPCTSTR)"Host %s try again later\n", host_name);
					OutputText(psBuff);
					break;

				case NO_RECOVERY:
					wsprintf(psBuff, (LPCTSTR)"Host %s DNS Error\n", host_name);
					OutputText(psBuff);
					break;

				case NO_ADDRESS:
					wsprintf(psBuff, (LPCTSTR)"No IP Address for %s\n", host_name);
					OutputText(psBuff);
					break;

				default:
					wsprintf(psBuff, (LPCTSTR)"Unknown Error: %s\n", (LPCTSTR)h_errno);
					OutputText(psBuff);
					break;
			}
		}
		else {
			for (p = hp->h_addr_list; *p != 0; p++) {
				struct in_addr in;
				char **q;

				memcpy(&in.s_addr, *p, sizeof(in.s_addr));

				wsprintf(psBuff, (LPCTSTR)"IP Address: %s\t Host Name: %s\n", inet_ntoa(in), hp->h_name);
				OutputText(psBuff);

				// Output the associated aliases
				for (q = hp->h_aliases; *q != 0; q++) {
					wsprintf(psBuff, (LPCTSTR)"\t\t\t\t Aliases: %s\n", *q);
					OutputText(psBuff);
				}
			}
		}
	}
	else {
		wsprintf(psBuff, (LPCTSTR)"Invalid host name: %s\n", host_name);
		OutputText(psBuff);
	}

	WSACleanup();
}

/*--------------------------------------------------------------------------------------- 
--	FUNCTION:	ws_addr_name
-- 
--	DATE:		January 26, 2009
-- 
--	REVISIONS:	
-- 
--	DESIGNER:	Steffen L. Norgren
-- 
--	PROGRAMMER:	Steffen L. Norgren
-- 
--	INTERFACE:	ws_addr_name(char * host_name)
--					LPDWORD ip_addr:	Long pointer to a DWORD holding the IP address	
-- 
--	RETURNS:	void
-- 
--	NOTES:	Gets the IP address associated with a canonical name associated and
--			outputs the results.
--
---------------------------------------------------------------------------------------*/
void ws_addr_name(LPDWORD ip_addr) {
	struct	hostent *hp;
	struct	in_addr my_addr, *addr_p;
	char	**p;
	LPSTR	psBuff;

	WORD wVersionRequested = MAKEWORD(2,2);
	WSADATA wsaData;

	psBuff = (LPSTR)VirtualAlloc((LPVOID)NULL, (DWORD)(255),
					MEM_COMMIT, PAGE_READWRITE);

	WSAStartup(wVersionRequested, &wsaData);

	OutputText((LPCTSTR)"\n");
	OutputText((LPCTSTR)"================ IP Address Lookup ================\n");

	addr_p = (struct in_addr*)malloc(sizeof(struct in_addr));
	addr_p = &my_addr;

	*ip_addr = htonl(*ip_addr);
	addr_p->s_addr = *ip_addr;

	hp = gethostbyaddr((char *)addr_p, PF_INET, sizeof(my_addr));

	if (hp == NULL) {
		wsprintf(psBuff, (LPCTSTR)"Host information for %s not found\n", inet_ntoa(my_addr));
		OutputText(psBuff);
	}
	else {
			for (p = hp->h_addr_list; *p != 0; p++) {
			struct in_addr in;
			char **q;

			memcpy(&in.s_addr, *p, sizeof(in.s_addr));

			wsprintf(psBuff, (LPCTSTR)"IP Address: %s\t Host Name: %s\n", inet_ntoa(in), hp->h_name);
			OutputText(psBuff);

			// Output the associated aliases
			for (q = hp->h_aliases; *q != 0; q++) {
				wsprintf(psBuff, (LPCTSTR)"\t\t\t\t Aliases: %s\n", *q);
				OutputText(psBuff);
			}
		}
	}

	WSACleanup();
}

/*--------------------------------------------------------------------------------------- 
--	FUNCTION:	ws_port_svc
-- 
--	DATE:		January 26, 2009
-- 
--	REVISIONS:	
-- 
--	DESIGNER:	Steffen L. Norgren
-- 
--	PROGRAMMER:	Steffen L. Norgren
-- 
--	INTERFACE:	ws_port_svc(char * port, char * proto)
--					char * port:	Port number string	
--					char * proto:	Protocol name string (i.e. TCP or UDP)
-- 
--	RETURNS:	void
-- 
--	NOTES:	Takes a user-specified port number and protocol in order to resolve it
--			into a service name and display the results.
--
---------------------------------------------------------------------------------------*/
void ws_port_svc(char * port, char * proto) {
	struct	servent *sv;
	int		s_port;
	LPSTR	psBuff;

	WORD wVersionRequested = MAKEWORD(2,2);
	WSADATA wsaData;

	psBuff = (LPSTR)VirtualAlloc((LPVOID)NULL, (DWORD)(255),
					MEM_COMMIT, PAGE_READWRITE);

	WSAStartup(wVersionRequested, &wsaData);

	OutputText((LPCTSTR)"\n");
	OutputText((LPCTSTR)"================ Resolving Port Number ================\n");

	s_port = atoi(port);

	sv = getservbyport(htons(s_port), proto);

	if (sv == NULL) {
		OutputText((LPCTSTR)"Error in getservbyport\n");
	}
	else {
		wsprintf(psBuff, (LPCTSTR)"The service for %s port %d is: %s\n",
			proto, ntohs(sv->s_port), sv->s_name);
		OutputText(psBuff);
	}

	WSACleanup();
}

/*--------------------------------------------------------------------------------------- 
--	FUNCTION:	ws_svc_port
-- 
--	DATE:		January 26, 2009
-- 
--	REVISIONS:	
-- 
--	DESIGNER:	Steffen L. Norgren
-- 
--	PROGRAMMER:	Steffen L. Norgren
-- 
--	INTERFACE:	ws_svc_port(char * port, char * proto)
--					char * service:	Service name string (i.e. http or ftp)	
--					char * proto:	Protocol name string (i.e. TCP or UDP)
-- 
--	RETURNS:	void
-- 
--	NOTES:	Takes a user-specified service name and protocol in order to resolve it
--			into its port number and display the results.
--
---------------------------------------------------------------------------------------*/
void ws_svc_port(char * service, char * proto) {
	struct	servent *sv;
	LPSTR	psBuff;

	WORD wVersionRequested = MAKEWORD(2,2);
	WSADATA wsaData;

	psBuff = (LPSTR)VirtualAlloc((LPVOID)NULL, (DWORD)(255),
					MEM_COMMIT, PAGE_READWRITE);

	WSAStartup(wVersionRequested, &wsaData);

	OutputText((LPCTSTR)"\n");
	OutputText((LPCTSTR)"================ Resolving Service Name ================\n");

	sv = getservbyname(service, proto);

	if (sv == NULL) {
		OutputText((LPCTSTR)"Error in getservbyname\n");
	}
	else {
		wsprintf(psBuff, (LPCTSTR)"The %s port number for %s is: %d\n", proto, service, ntohs(sv->s_port));
		OutputText(psBuff);
	}

	WSACleanup();
}