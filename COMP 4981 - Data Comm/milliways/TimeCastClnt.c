/*
 * TimeCastClnt.c              (c) Bob Quinn              3/15/97
 *
 * Released to the public domain
 *
 * Description:
 *  Sample multicast client (receiver) application that sets the
 *  system time according to the server setting sent.
 */
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#define BUFSIZE     1024
#define MAXADDRSTR  16

#define TIMECAST_ADDR "234.5.6.7"
#define TIMECAST_PORT 8910

char achMCAddr[MAXADDRSTR] = TIMECAST_ADDR;
u_long lMCAddr;
u_short nPort              = TIMECAST_PORT;
SYSTEMTIME *lpstSysTime, stSysTime;

void show_usage(void) {
  printf("usage: TimeCastClnt [multicast address][:port number]\n\n");
  printf("  multicast address: 224.0.0.0 to 239.255.255.255\n");
  printf("  port number:       server's port number (16-bit)\n\n");
  printf("If none provided, default values are %s:%d.\n", 
      TIMECAST_ADDR, TIMECAST_PORT);
} 

int main(int argc, char *argv[]) {
  int nRet;
  int nIP_TTL = 2;
  BOOL  fFlag;
  SOCKADDR_IN stLclAddr, stSrcAddr;
  struct ip_mreq stMreq;         /* Multicast interface structure */
  SOCKET hSocket;
  char achInBuf [BUFSIZE];
  WSADATA stWSAData;

  /* Display program banner */
  printf("------------------------------------------------------\n");
  printf(" TimeCastClnt - multicast time client   (c) Bob Quinn\n");
  printf("------------------------------------------------------\n");

  /* Process input arguments */
  if ((argc > 2) || 
      ((argc == 2) &&
       (((strcmp(argv[1], "-help") == 0) || 
         (strcmp(argv[1], "-?") == 0)))))  {
      show_usage();
      exit(1);
  }

  /* Init WinSock */
  nRet = WSAStartup(0x0202, &stWSAData);
  if (nRet) {
      printf ("WSAStartup failed: %d\r\n", nRet);
      exit(1);
  }

  if (argc == 2) {
    char *strTmp;
    strTmp = strchr(argv[1],':');
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
      if (argv[1] != '\0') {
          /* Evaluate multicast address provided */
          lMCAddr = inet_addr(argv[1]);
          if (!((lMCAddr>=0xe0000000) || (lMCAddr<=0xefffffff))){
            printf ("Invalid address %s provided by user.\n", 
                argv[1]);
            printf ("using default address: %s\n", achMCAddr);
          } else {
            strcpy (achMCAddr, argv[1]);  /* Address looks ok */
          }
      }
  }

  /* Get a datagram socket */
  hSocket = socket(AF_INET, 
     SOCK_DGRAM, 
     0);
  if (hSocket == INVALID_SOCKET) {
    printf ("socket() failed, Err: %d\n", WSAGetLastError());
    WSACleanup();
    exit(1);
  }

  /* Avoid (WSA)EADDRINUSE error on bind() (last one to bind should 
   *  receive dgrams sent to our port, but there are no guarantees of 
   *  this, unfortunately). */ 
  fFlag = TRUE;
  nRet = setsockopt(hSocket, 
     SOL_SOCKET, 
     SO_REUSEADDR, 
     (char *)&fFlag, 
     sizeof(fFlag));
  if (nRet == SOCKET_ERROR) {
    printf ("setsockopt() SO_REUSEADDR failed, Err: %d\n",
      WSAGetLastError());
  }

  /* Name the socket (assign the local port number to receive on) */
  stLclAddr.sin_family      = AF_INET;
  stLclAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  stLclAddr.sin_port        = htons(nPort);
  nRet = bind(hSocket, 
      (struct sockaddr*) &stLclAddr, 
      sizeof(stLclAddr));
  if (nRet == SOCKET_ERROR) {
      printf ("bind() port: %d failed, Err: %d\n", nPort, 
      WSAGetLastError());
  }

  /* Join the multicast group so we can receive from it */
  stMreq.imr_multiaddr.s_addr = inet_addr(achMCAddr);
  stMreq.imr_interface.s_addr = INADDR_ANY;
  nRet = setsockopt(hSocket, 
     IPPROTO_IP, 
     IP_ADD_MEMBERSHIP, 
     (char *)&stMreq, 
     sizeof(stMreq));
  if (nRet == SOCKET_ERROR) {
    printf(
      "setsockopt() IP_ADD_MEMBERSHIP address %s failed, Err: %d\n",
      achMCAddr, WSAGetLastError());
  } 

  printf("Now waiting for time updates from the TimeCast server\n");
  printf("  multicast group address: %s, port number: %d\n",
      achMCAddr, nPort);
  lpstSysTime = (SYSTEMTIME *)achInBuf;
  for (;;) {
    int addr_size = sizeof(struct sockaddr_in);

    nRet = recvfrom(hSocket, 
      achInBuf, 
      BUFSIZE, 
      0,
      (struct sockaddr*)&stSrcAddr, 
      &addr_size);
    if (nRet < 0) {
      printf ("recvfrom() failed, Error: %d\n", WSAGetLastError());
      WSACleanup();
      exit(1);
    }

    printf(
     "UTC Time %02d:%02d:%02d:%03d on %02d-%02d-%d from %s:%d\n",
      lpstSysTime->wHour,   lpstSysTime->wMinute, 
      lpstSysTime->wSecond, lpstSysTime->wMilliseconds,
      lpstSysTime->wMonth,  lpstSysTime->wDay,  lpstSysTime->wYear,
      inet_ntoa(stSrcAddr.sin_addr), 
      ntohs(stSrcAddr.sin_port));

    /* Set the local time using the system (UTC) time from server */
    nRet = SetSystemTime(lpstSysTime);
    if (!nRet) {
        printf ("SetLocalTime() failed, Err: %d\n", 
            GetLastError());
    } else {
      GetLocalTime(&stSysTime);
      printf (
      " Local Time reset to %02d-%02d-%02d at %02d:%02d:%02d:%03d\n",
        stSysTime.wMonth,  stSysTime.wDay,  stSysTime.wYear,
        stSysTime.wHour,   stSysTime.wMinute, 
        stSysTime.wSecond, stSysTime.wMilliseconds);
    }
  } /* end for(;;) */

  /* Leave the multicast group: With IGMP v1 this is a noop, but 
   *  with IGMP v2, it may send notification to multicast router.
   *  Even if it's a noop, it's sanitary to cleanup after one's self.
   */
  stMreq.imr_multiaddr.s_addr = inet_addr(achMCAddr);
  stMreq.imr_interface.s_addr = INADDR_ANY;
  nRet = setsockopt(hSocket, 
     IPPROTO_IP, 
     IP_DROP_MEMBERSHIP, 
     (char *)&stMreq, 
     sizeof(stMreq));
  if (nRet == SOCKET_ERROR) {
    printf (
      "setsockopt() IP_DROP_MEMBERSHIP address %s failed, Err: %d\n",
      achMCAddr, WSAGetLastError());
  } 

  /* Close the socket */
  closesocket(hSocket);

  /* Tell WinSock we're leaving */
  WSACleanup();

  return (0);
} /* end main() */
