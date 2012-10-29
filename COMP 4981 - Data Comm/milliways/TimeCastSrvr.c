/*
 * TimeCastSrvr.c              (c) Bob Quinn              3/15/97
 *
 * Released to the public domain
 *
 * Description:
 *  Sample multicast server (sender) application that multicasts the
 *  system time for clients (receivers) to use to set their clocks.
 */
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#define BUFSIZE     1024
#define MAXADDRSTR  16

#define TIMECAST_ADDR   "234.5.6.7"
#define TIMECAST_PORT   8910
#define TIMECAST_TTL    2
#define TIMECAST_INTRVL 30

char achMCAddr[MAXADDRSTR] = TIMECAST_ADDR;
u_long lMCAddr;
u_short nPort              = TIMECAST_PORT;
u_long  lTTL               = TIMECAST_TTL;
u_short nInterval          = TIMECAST_INTRVL;
SYSTEMTIME stSysTime;

void show_usage(void) {
  printf(
      "usage: TimeCastSrvr [-g multicast address][:port number]\n");
  printf("                    [-i interval]\n");
  printf("                    [-t IP time-to-live\n\n");
  printf("  multicast address: 224.0.0.0 to 239.255.255.255\n");
  printf("  port number:       server's port\n\n");
  printf("If none provided, default values are %s:%d.\n", 
      TIMECAST_ADDR, TIMECAST_PORT);
  printf("  interval:        seconds between sends (default: 30)\n");
  printf("  IP time-to-live: number of router hops (default: 2)\n");
} 

int main(int argc, char *argv[]) {
  int nRet, i;
  BOOL  fFlag;
  SOCKADDR_IN stLclAddr, stDstAddr;
  struct ip_mreq stMreq;        /* Multicast interface structure */
  SOCKET hSocket;
  WSADATA stWSAData;

  /* Display program banner */
  printf("------------------------------------------------------\n");
  printf(" TimeCastSrvr - multicast time server   (c) Bob Quinn\n");
  printf("------------------------------------------------------\n");

  /* Process input arguments */
  if ((argc == 2) &&
      ((strcmp(argv[1],"-help")==0) || (strcmp(argv[1],"-?")==0))) {
    show_usage();
    exit(1);
  }

  /* Init WinSock */
  nRet = WSAStartup(0x0202, &stWSAData);
  if (nRet) {
      printf ("WSAStartup failed: %d\r\n", nRet);
      exit (1);
  }

  fFlag = FALSE;
  for (i=1; i<argc; i++) {
    char *strTmp;
    if (fFlag) {
        fFlag = FALSE;
        continue;
    }
    if (!((argv[i][0] == '-') || (argv[i][0] == '/'))) {
        show_usage();
        WSACleanup();
        exit(0);
    }
    /* Multicast Group Address and Port setting */
    if (argv[i][1] == 'g') {
        fFlag = TRUE;
        strTmp = strchr(argv[i+1],':');
        /* Get user port number (in host order) */
        if (strTmp) {
            *strTmp = '\0';
            nPort = atoi(++strTmp);
            if (nPort == 0) {
                printf("Invalid port number provided by user.\n");
                printf("using default port number: %d\n",
                    TIMECAST_PORT);
                nPort = TIMECAST_PORT;
            }
        }
        /* Get user multicast address */
        if (argv[i+1] != '\0') {
            /* Evaluate multicast address provided */
            lMCAddr = inet_addr(argv[i+1]);
            if (!((lMCAddr >= 0xe0000000) || 
                  (lMCAddr <= 0xefffffff))) {
                printf ("Invalid address %s provided by user.\n", 
                    argv[1]);
                printf ("using default address: %s\n", achMCAddr);
            } else {
                strcpy (achMCAddr, argv[i+1]); /* Address is ok */
            }
        }
        continue;
    }
    /* Multicast Interval setting (how often to send) */
    if (argv[i][1] == 'i') {
        fFlag = TRUE;
        nInterval = atoi(argv[i+1]);
        if (nInterval == 0) {
            printf (
              "Invalid interval, using default of %d seconds.\n",
              TIMECAST_INTRVL);
            nInterval = TIMECAST_INTRVL;
        }
        continue;
    }
    /* IP time-to-live setting (scope of multicast send) */
    if (argv[i][1] == 't') {
        fFlag = TRUE;
        lTTL = atoi(argv[i+1]);
        if ((lTTL <= 0) || (lTTL > 255)) {
            printf (
              "Invalid IP time-to-live, using default of %d.\n",
              TIMECAST_TTL);
        }
    }
  }

  /* Display current settings */
  printf ("Multicast Address:%s, Port:%d, IP TTL:%d, Interval:%d\n",
    achMCAddr, nPort, lTTL, nInterval);

  /* Get a datagram socket */
  hSocket = socket(AF_INET, 
     SOCK_DGRAM, 
     0);
  if (hSocket == INVALID_SOCKET) {
    printf ("socket() failed, Err: %d\n", WSAGetLastError());
    exit(1);
  }

  /* Bind the socket
   * 
   * NOTE: Normally, we wouldn't need to call bind unless we were 
   *  assigning a local port number explicitly (naming the socket), 
   *  however Microsoft requires that a socket be bound before it 
   *  can join a multicast group with setsockopt() IP_ADD_MEMBERSHIP 
   *  (or fails w/ WSAEINVAL).
   */
  stLclAddr.sin_family      = AF_INET; 
  stLclAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* any interface */
  stLclAddr.sin_port        = 0;                 /* any port */
  nRet = bind(hSocket, 
      (struct sockaddr*) &stLclAddr, 
      sizeof(stLclAddr));
  if (nRet == SOCKET_ERROR) {
      printf ("bind() port: %d failed, Err: %d\n", nPort, 
      WSAGetLastError());
  }

  /* Join the multicast group
   * 
   * NOTE: According to RFC 1112, a sender does not need to join the 
   *  group, however Microsoft requires a socket to join a group in 
   *  order to use setsockopt() IP_MULTICAST_TTL (or fails with error
   *  WSAEINVAL).
   */
  stMreq.imr_multiaddr.s_addr = inet_addr(achMCAddr);
  stMreq.imr_interface.s_addr = INADDR_ANY;
  nRet = setsockopt(hSocket, 
     IPPROTO_IP, 
     IP_ADD_MEMBERSHIP, 
     (char *)&stMreq, 
     sizeof(stMreq));
  if (nRet == SOCKET_ERROR) {
    printf (
      "setsockopt() IP_ADD_MEMBERSHIP address %s failed, Err: %d\n",
      achMCAddr, WSAGetLastError());
  } 

  /* Set IP TTL to traverse up to multiple routers */
  nRet = setsockopt(hSocket, 
     IPPROTO_IP, 
     IP_MULTICAST_TTL, 
     (char *)&lTTL, 
     sizeof(lTTL));
  if (nRet == SOCKET_ERROR) {
    printf ("setsockopt() IP_MULTICAST_TTL failed, Err: %d\n",
      WSAGetLastError());
  }

  /* Disable loopback */
  fFlag = FALSE;
  nRet = setsockopt(hSocket, 
     IPPROTO_IP, 
     IP_MULTICAST_LOOP, 
     (char *)&fFlag, 
     sizeof(fFlag));
  if (nRet == SOCKET_ERROR) {
    printf ("setsockopt() IP_MULTICAST_LOOP failed, Err: %d\n",
      WSAGetLastError());
  }

  /* Assign our destination address */
  stDstAddr.sin_family =      AF_INET;
  stDstAddr.sin_addr.s_addr = inet_addr(achMCAddr);
  stDstAddr.sin_port =        htons(nPort);
  for (;;) {
    /* Get System (UTC) Time */
    GetSystemTime (&stSysTime);

    /* Send the time to our multicast group! */
    nRet = sendto(hSocket, 
      (char *)&stSysTime, 
      sizeof(stSysTime),
      0,
      (struct sockaddr*)&stDstAddr, 
      sizeof(stDstAddr));
    if (nRet < 0) {
      printf ("sendto() failed, Error: %d\n", WSAGetLastError());
      exit(1);
    } else {
        printf("Sent UTC Time %02d:%02d:%02d:%03d ",
            stSysTime.wHour, 
            stSysTime.wMinute, 
            stSysTime.wSecond,
			stSysTime.wMilliseconds);
        printf("Date: %02d-%02d-%02d to: %s:%d\n",
            stSysTime.wMonth, 
            stSysTime.wDay, 
            stSysTime.wYear, 
            inet_ntoa(stDstAddr.sin_addr), 
            ntohs(stDstAddr.sin_port));
    }

    /* Wait for the specified interval */
    Sleep(nInterval*1000);

  } /* end for(;;) */

  /* Close the socket */
  closesocket(hSocket);

  /* Tell WinSock we're leaving */
  WSACleanup();

  return (0);
} /* end main() */
