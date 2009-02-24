/*---------------------------------------------------------------------------------------
--	SOURCE FILE:	wsTools.c -   Handles all Winsock requests for the program.
--
--	PROGRAM:		datagram_analyzer.exe
--
--	FUNCTIONS:		ws_name_addr(char * host_name)
--					ws_addr_name(LPDWORD ip_addr)
--
--
--	DATE:			January 26, 2009
--
--	REVISIONS:		February 20, 2009 - Modified for use in new program.
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
#include <commctrl.h>
#include "winMain.h"
#include "wsTools.h"

/*--------------------------------------------------------------------------------------- 
--	FUNCTION:	ws_name_addr
-- 
--	DATE:		January 26, 2009
-- 
--	REVISIONS:	February 20, 2009 - Removed all references to OutputText(char *)
--								  - Function now produces message boxes for errors
--								  - Function now returns an int if successful
--								  - Function sets global IP and host name
-- 
--	DESIGNER:	Steffen L. Norgren
-- 
--	PROGRAMMER:	Steffen L. Norgren
-- 
--	INTERFACE:	ws_name_addr(char * host_name)
--					char * host_name:	A host name string
-- 
--	RETURNS:	0 if invalid
--				1 if valid
-- 
--	NOTES:	Gets the IP address associated with a canonical name and saves the results.
--
---------------------------------------------------------------------------------------*/
int ws_name_addr(char * host_name) {
	struct	hostent *hp;
	struct	in_addr in;
	char	**p;
	LPSTR	psBuff;
	BYTE	ip[4];

	WORD wVersionRequested = MAKEWORD(2,2);
	WSADATA wsaData;

	psBuff = (LPSTR)VirtualAlloc((LPVOID)NULL, (DWORD)(255),
					MEM_COMMIT, PAGE_READWRITE);

	WSAStartup(wVersionRequested, &wsaData);

	if (!isdigit(*host_name)) { // must not be an IP address
		if ((hp = gethostbyname(host_name)) == NULL) { // Host name?
			switch(h_errno) {
				case HOST_NOT_FOUND:
					wsprintf(psBuff, (LPCTSTR)"No such host %s\n", host_name);
					MessageBox(ghWndMain, psBuff, NULL, MB_OK | MB_ICONSTOP);
					WSACleanup();
					return 0;

				case TRY_AGAIN:
					wsprintf(psBuff, (LPCTSTR)"Host %s try again later\n", host_name);
					MessageBox(ghWndMain, psBuff, NULL, MB_OK | MB_ICONSTOP);
					WSACleanup();
					return 0;

				case NO_RECOVERY:
					wsprintf(psBuff, (LPCTSTR)"Host %s DNS Error\n", host_name);
					MessageBox(ghWndMain, psBuff, NULL, MB_OK | MB_ICONSTOP);
					WSACleanup();
					return 0;

				case NO_ADDRESS:
					wsprintf(psBuff, (LPCTSTR)"No IP Address for %s\n", host_name);
					MessageBox(ghWndMain, psBuff, NULL, MB_OK | MB_ICONSTOP);
					WSACleanup();
					return 0;

				default:
					wsprintf(psBuff, (LPCTSTR)"Unknown Error: %s\n", (LPCTSTR)h_errno);
					MessageBox(ghWndMain, psBuff, NULL, MB_OK | MB_ICONSTOP);
					WSACleanup();
					return 0;
			}
		}
		else {
			for (p = hp->h_addr_list; *p != 0; p++) {
				memcpy(&in.s_addr, *p, sizeof(in.s_addr));
				wsprintf(psBuff, (LPCTSTR)"IP Address: %s\t Host Name: %s\n", inet_ntoa(in), hp->h_name);
			}
		}
	}
	else {
		wsprintf(psBuff, (LPCTSTR)"Invalid host name: %s\n", host_name);
	}

	WSACleanup();

	gHostName = hp->h_name;

	// Set our global addresses
	ip[0] = FIRST_IPADDRESS(in.s_addr);
	ip[1] = SECOND_IPADDRESS(in.s_addr);
	ip[2] = THIRD_IPADDRESS(in.s_addr);
	ip[3] = FOURTH_IPADDRESS(in.s_addr);
	gIP = MAKEIPADDRESS(ip[3], ip[2], ip[1], ip[0]);

	return 1;
}

/*--------------------------------------------------------------------------------------- 
--	FUNCTION:	ws_addr_name
-- 
--	DATE:		January 26, 2009
-- 
--	REVISIONS:	February 20, 2009 - Removed all references to OutputText(char *)
--								  - Function now produces message boxes for errors
--								  - Function now returns an int if successful
--								  - Function sets global IP and host name
-- 
--	DESIGNER:	Steffen L. Norgren
-- 
--	PROGRAMMER:	Steffen L. Norgren
-- 
--	INTERFACE:	ws_addr_name(char * host_name)
--					LPDWORD ip_addr:	Long pointer to a DWORD holding the IP address	
-- 
--	RETURNS:	0 if invalid
--				1 if valid
-- 
--	NOTES:	Gets the canonical name associated with an internet IP address and
--			saves the results.
--
---------------------------------------------------------------------------------------*/
int ws_addr_name(LPDWORD ip_addr) {
	struct	hostent *hp;
	struct	in_addr in;
	struct	in_addr my_addr, *addr_p;
	char	**p;
	LPSTR	psBuff;
	BYTE	ip[4];

	WORD wVersionRequested = MAKEWORD(2,2);
	WSADATA wsaData;

	psBuff = (LPSTR)VirtualAlloc((LPVOID)NULL, (DWORD)(255),
					MEM_COMMIT, PAGE_READWRITE);

	WSAStartup(wVersionRequested, &wsaData);

	addr_p = (struct in_addr*)malloc(sizeof(struct in_addr));
	addr_p = &my_addr;

	*ip_addr = htonl(*ip_addr);
	addr_p->s_addr = *ip_addr;

	hp = gethostbyaddr((char *)addr_p, PF_INET, sizeof(my_addr));

	if (hp == NULL) {
		wsprintf(psBuff, (LPCTSTR)"Host information for %s not found\n", inet_ntoa(my_addr));
		MessageBox(ghWndMain, psBuff, NULL, MB_OK | MB_ICONSTOP);
		WSACleanup();
		return 0;
	}
	else {
		for (p = hp->h_addr_list; *p != 0; p++) {
			memcpy(&in.s_addr, *p, sizeof(in.s_addr));

			wsprintf(psBuff, (LPCTSTR)"IP Address: %s\t Host Name: %s\n", inet_ntoa(in), hp->h_name);
		}
	}

	WSACleanup();

	// Set our global addresses
	gHostName = hp->h_name;
	ip[0] = FIRST_IPADDRESS(*ip_addr);
	ip[1] = SECOND_IPADDRESS(*ip_addr);
	ip[2] = THIRD_IPADDRESS(*ip_addr);
	ip[3] = FOURTH_IPADDRESS(*ip_addr);
	gIP = MAKEIPADDRESS(ip[3], ip[2], ip[1], ip[0]);

	return 1;
}