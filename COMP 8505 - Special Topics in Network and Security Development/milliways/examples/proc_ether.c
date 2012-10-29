/*---------------------------------------------------------------------------------------------
--	SOURCE FILE:	proc_ether.c -   Process Ethernet packets
--
--	FUNCTIONS:		libpcap - packet filtering library based on the BSD packet
--					filter (BPF)
--
--	DATE:			April 23, 2006
--
--	REVISIONS:		(Date and nic_description)
--
--	DESIGNERS:		Based on the code by Martin Casado 
--					Also code was taken from tcpdump source, namely the following files..
--					print-ether.c
--					print-ip.c
--					ip.h
--					Modified & redesigned: Aman Abdulla: April 23, 2006
--
--	PROGRAMMER:		Aman Abdulla
--
--	NOTES:
--	The program will process packets passed to it to determine the type of Ethernet packet
--	it is: IP, ARP, or RARP packets. It will also print out the src and dst MAC addresses.
-------------------------------------------------------------------------------------------------*/
#include <pcap.h>
#include <netinet/if_ether.h> 
#include <netinet/ip.h>
#include <netinet/ether.h> 
#include "pkt_sniffer.h"

u_int16_t handle_ethernet (u_char *args,const struct pcap_pkthdr* pkthdr,const u_char* packet)
{
    	u_int caplen = pkthdr->caplen;
    	u_int length = pkthdr->len;
    	struct ether_header *eptr;  /* net/ethernet.h */
    	u_short ether_type;

    	if (caplen < ETHER_HDRLEN)
    	{
        	fprintf(stdout,"Packet length less than ethernet header length\n");
        	return -1;
    	}

    	// Start with the Ethernet header... 
    	eptr = (struct ether_header *) packet;
    	ether_type = ntohs(eptr->ether_type);

    	// Print SOURCE DEST TYPE LENGTH fields
   		fprintf(stdout,"ETH: ");
    	fprintf(stdout,"%s ", ether_ntoa((struct ether_addr*)eptr->ether_shost));
    	fprintf(stdout,"%s ",ether_ntoa((struct ether_addr*)eptr->ether_dhost));

    	// Check to see if we have an IP packet 
    	if (ether_type == ETHERTYPE_IP)
    	{
        	fprintf(stdout,"(IP)");
    	}
		else  if (ether_type == ETHERTYPE_ARP)
    	{
        	fprintf(stdout,"(ARP)");
    	}
		else  if (eptr->ether_type == ETHERTYPE_REVARP)
    	{
        	fprintf(stdout,"(RARP)");
    	}
		else 
		{
        	fprintf(stdout,"(?)");
    	}
    	fprintf(stdout," %d\n",length);

    	return ether_type;
}
