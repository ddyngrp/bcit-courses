/*------------------------------------------------------------------------------
--	SOURCE FILE:	getinfo.c -   This file implements the functions to
--										  retrieve network interface information.
--
--
--	FUNCTIONS:		Get_ifi_info
--                get_ifi_info
--						free_ifi_info
--
--	DATE:				March 9, 2001
--
--	REVISIONS:	  (Date and Description)
--
--	DESIGNERS:     Based on the examples by Stevens (Ch. 16)
--						Modified and redesigned: Aman Abdulla
--
--	PROGRAMMER:		Aman Abdulla
--
--	NOTES:
--	This is where the functions called from ifinfo.c are implemented.
------------------------------------------------------------------------------*/
#include <sys/ioctl.h>
#include <errno.h>
#include <net/if_arp.h>
#include	"ictl.h"

// Globals

char *ptr;
u_char *hptr;

/*------------------------------------------------------------------------------
--
--	FUNCTION:		Get_ifi_info
--
--	DATE:				March 9, 2001
--
--	REVISIONS:	  (Date and Description)
--
--	DESIGNERS:     Based on the examples by Stevens (Ch. 16)
--						Modified and redesigned: Aman Abdulla
--
--	PROGRAMMER:	Aman Abdulla
--
-- INTERFACE: struct ifi_info * Get_ifi_info (int family, int doaliases)
--
--	RETURNS:  Details in the actual get_ifi_info header.
--
--	NOTES:
--	This is simply a wrapper function that calls the actual get_ifi_info
--	function.
------------------------------------------------------------------------------*/
struct ifi_info * Get_ifi_info (int family, int doaliases)
{
	struct ifi_info	*ifi;

	if ( (ifi = get_ifi_info (family, doaliases)) == NULL)
		perror("Get_ifi_info error");
	return(ifi);
}

/*------------------------------------------------------------------------------
--
--	FUNCTION:		get_ifi_info
--
--	DATE:				March 9, 2001
--
--	REVISIONS:	  (Date and Description)
--
--	DESIGNERS:     Based on the examples by Stevens (Ch. 16)
--						Modified and redesigned: Aman Abdulla
--
--	PROGRAMMER:	Aman Abdulla
--
-- INTERFACE: struct ifi_info * get_ifi_info (int family, int doaliases)
--									 family: The address family. Usually AF_INET
--									 doaliases: Number of aliases to process.
--
--	RETURNS:  Returns a pointer to the head of a linked list of ifi_info
--				 structures (ictl.h).
--
--	NOTES:
--	This creates an information structure for each interface that is "up" and
--	chains all the structures in a linked-list. The ioctl system call is used
--	to obtain all the interface information. The function also detects any
-- additonal addresses that have been assigned to the interface (aliases).
------------------------------------------------------------------------------*/
struct ifi_info * get_ifi_info(int family, int doaliases)
{
	struct ifi_info *ifi, *ifihead, **ifipnext;
	int sockfd, len, lastlen, flags, myflags;
	char *ptr, *buf, lastname[IFNAMSIZ], *cptr;
	struct ifconf ifc;
	struct ifreq *ifr, ifrcopy;
	struct sockaddr_in *sinptr;

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
		perror ("socket:\n");
		exit(1);
	}

	lastlen = 0;
	len = 100 * sizeof(struct ifreq);	/* initial buffer size guess */
	for ( ; ; )
	{
		if ((buf = malloc(len)) == NULL)
		{
			perror ("malloc:\n");
			exit(1);
		}
		ifc.ifc_len = len;
		ifc.ifc_buf = buf;

		// Get the list of all interfaces
		// Note that SIOCGIFCONF will also return the IP address of the interfaces
		if (ioctl (sockfd, SIOCGIFCONF, &ifc) < 0)
		{
			if (errno != EINVAL || lastlen != 0)
			{
				perror("ioctl SIOCGIFCONF");
				exit(1);
			}
		}
		else
		{
			if (ifc.ifc_len == lastlen)
				break;		/* success, len has not changed */
			lastlen = ifc.ifc_len;
		}
		len += 10 * sizeof(struct ifreq);	/* increment */
		free(buf);

	}
	ifihead = NULL;
	ifipnext = &ifihead;
	lastname[0] = 0;

	for (ptr = buf; ptr < buf + ifc.ifc_len; )
	{
		ifr = (struct ifreq *) ptr;
      len = sizeof(struct sockaddr);
		ptr += sizeof(ifr->ifr_name) + len;	/* for next one in buffer */

		if (ifr->ifr_addr.sa_family != family)
			continue;	/* ignore if not desired address family */

		myflags = 0;
		if ( (cptr = strchr(ifr->ifr_name, ':')) != NULL)
			*cptr = 0;		/* replace colon will null */

		if (strncmp(lastname, ifr->ifr_name, IFNAMSIZ) == 0)
		{
			if (doaliases == 0)
				continue;	/* already processed this interface */
			myflags = IFI_ALIAS;
		}
		memcpy (lastname, ifr->ifr_name, IFNAMSIZ);

		ifrcopy = *ifr;

		// Get the interface flags
		if ((ioctl (sockfd, SIOCGIFFLAGS, &ifrcopy)) < 0)
		{
			perror ("ioctl SIOCGIFFLAGS:\n");
			exit(1);
		}
		flags = ifrcopy.ifr_flags;
		if ((flags & IFF_UP) == 0)
			continue;	/* ignore if interface not up */

		if ((ifi = calloc(1, sizeof(struct ifi_info))) == NULL)
		{
			perror("calloc:\n");
			exit(1);
		}

		*ifipnext = ifi;					/* prev points to this new one */
		ifipnext = &ifi->ifi_next;		/* pointer to next one goes here */
                            ifi->ifi_flags = flags;		/* IFF_xxx values */
		ifi->ifi_myflags = myflags;		/* IFI_xxx values */
		memcpy (ifi->ifi_name, ifr->ifr_name, IFI_NAME);
		ifi->ifi_name[IFI_NAME-1] = '\0';

		sinptr = (struct sockaddr_in *) &ifr->ifr_addr;
		if (ifi->ifi_addr == NULL)
		{
			if ((ifi->ifi_addr = calloc(1, sizeof(struct sockaddr_in))) == NULL)
			{
				perror("calloc:\n");
				exit(1);
			}
			// copy the IP address returned by the original SIOCGIFCONF  request
			memcpy(ifi->ifi_addr, sinptr, sizeof(struct sockaddr_in));

			//Get broadcast address
			if (flags & IFF_BROADCAST)
			{
				if ((ioctl (sockfd, SIOCGIFBRDADDR, &ifrcopy)) < 0)
				{
					perror ("ioctl SIOCGIFBRDADDR:\n");
					exit(1);
				}
				sinptr = (struct sockaddr_in *) &ifrcopy.ifr_broadaddr;
				if ((ifi->ifi_brdaddr = calloc(1, sizeof(struct sockaddr_in))) == NULL)
				{
					perror("calloc:\n");
					exit(1);
				}
				// copy the Broadcast address
				memcpy(ifi->ifi_brdaddr, sinptr, sizeof(struct sockaddr_in));
			}

			// Get point-point address
			if (flags & IFF_POINTOPOINT)
			{
				if ((ioctl (sockfd, SIOCGIFDSTADDR, &ifrcopy)) < 0)
				{
					perror ("ioctl SIOCGIFDSTADDR:\n");
					exit(1);
				}
				sinptr = (struct sockaddr_in *) &ifrcopy.ifr_dstaddr;
				if ((ifi->ifi_dstaddr = calloc(1, sizeof(struct sockaddr_in))) == NULL)
				{
					perror("calloc:\n");
					exit(1);
				}
				// copy the Point-to-Point address
				memcpy(ifi->ifi_dstaddr, sinptr, sizeof(struct sockaddr_in));

			}
			// Get the hardware address
			if ((ioctl (sockfd, SIOCGIFHWADDR, &ifrcopy)) < 0)
			{
				perror ("ioctl SIOCGIFHWADDR: \n");
				exit(1);
			}
			else
			{
				sinptr = (struct sockaddr_in *) &ifrcopy.ifr_hwaddr;
				if ((ifi->ifi_hwaddr = calloc(1, sizeof(struct sockaddr_in))) == NULL)
				{
					perror("calloc:\n");
					exit(1);
				}
				// copy the HW address
				memcpy(ifi->ifi_hwaddr, sinptr, sizeof(struct sockaddr_in));
			}
		}
	}
	free(buf);
	return(ifihead);	/* pointer to first structure in linked list */
}

/*------------------------------------------------------------------------------
--
--	FUNCTION:		free_ifi_info
--
--	DATE:				March 9, 2001
--
--	REVISIONS:	  (Date and Description)
--
--	DESIGNERS:     Stevens (Ch. 16)
--
--	PROGRAMMER:	   Richard Stevens
--
-- INTERFACE: void free_ifi_info (struct ifi_info *ifihead)
--   					 *ifihead : pointer to the start of the linked-list.
--
--	RETURNS:  Void.
--
--	NOTES:
--	This function takes a pointer to the start of a linked-list of ifi_info
--	structures and frees all the dynamic memory assigned by get_ifi_info.
------------------------------------------------------------------------------*/
void free_ifi_info(struct ifi_info *ifihead)
{
	struct ifi_info	*ifi, *ifinext;

	for (ifi = ifihead; ifi != NULL; ifi = ifinext) {
		if (ifi->ifi_addr != NULL)
			free(ifi->ifi_addr);
		if (ifi->ifi_brdaddr != NULL)
			free(ifi->ifi_brdaddr);
		if (ifi->ifi_dstaddr != NULL)
			free(ifi->ifi_dstaddr);
		ifinext = ifi->ifi_next;	/* can't fetch ifi_next after free() */
		free(ifi);			/* the ifi_info{} itself */
	}
}

