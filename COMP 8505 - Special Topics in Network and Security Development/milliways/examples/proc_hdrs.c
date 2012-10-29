/*---------------------------------------------------------------------------------------------
--	SOURCE FILE:	proc_hdrs.c -   program to process the packet headers
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
--	The program is designed to process and parse the individual will parse the headers and 
--	print out selected fields of interest.
--	Currently the only the IP header processing functionality has been implemented.  
-------------------------------------------------------------------------------------------------*/

#include <pcap.h>
#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h> 
#include <net/ethernet.h>
#include <netinet/ether.h> 
#include <netinet/ip.h> 
#include "pkt_sniffer.h"


// Check all the headers in the Ethernet frame
void pkt_callback(u_char *args,const struct pcap_pkthdr* pkthdr,const u_char* packet)
{
    	u_int16_t type = handle_ethernet(args,pkthdr,packet);

    	if(type == ETHERTYPE_IP) // handle the IP packet
    	{
        	handle_IP(args,pkthdr,packet);
    	}
		else if (type == ETHERTYPE_ARP) // handle the ARP packet 
		{
    	}
    	else if (type == ETHERTYPE_REVARP) // handle reverse arp packet 
		{
    	}
}


// This function will parse the IP header and print out selectd fields of interest
u_char* handle_IP (u_char *args,const struct pcap_pkthdr* pkthdr,const u_char* packet)
{
    	const struct my_ip* ip;
    	u_int length = pkthdr->len;
    	u_int hlen,off,version;
    	int len;

    	// Jump past the Ethernet header 
    	ip = (struct my_ip*)(packet + sizeof(struct ether_header));
    	length -= sizeof(struct ether_header); 

    	// make sure that the packet is of a valid length 
    	if (length < sizeof(struct my_ip))
    	{
        	printf("Truncated IP %d",length);
        	return NULL;
    	}

    	len     = ntohs(ip->ip_len);
    	hlen    = IP_HL(ip); 	// get header length 
    	version = IP_V(ip);	// get the IP version number

    	// verify version 
    	if(version != 4)
    	{
      		fprintf(stdout,"Unknown version %d\n",version);
      		return NULL;
    	}

    	// verify the header length */
    	if(hlen < 5 )
    	{
        	fprintf(stdout,"Bad header length %d \n",hlen);
    	}

    	// Ensure that we have as much of the packet as we should 
    	if (length < len)
        	printf("\nTruncated IP - %d bytes missing\n",len - length);

    	// Ensure that the first fragment is present
    	off = ntohs(ip->ip_off);
    	if ((off & 0x1fff) == 0 ) 	// i.e, no 1's in first 13 bits 
    	{				// print SOURCE DESTINATION hlen version len offset */
        	fprintf(stdout,"IP: ");
        	fprintf(stdout,"%s ", inet_ntoa(ip->ip_src));
        	fprintf(stdout,"%s %d %d %d %d\n", inet_ntoa(ip->ip_dst), hlen,version,len,off);
    	}
    	return NULL;
}
