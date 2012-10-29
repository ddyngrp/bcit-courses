/*---------------------------------------------------------------------------------------
--	SOURCE FILE:	pkt_cap1.c -   A simple packet capture program
--
--	FUNCTIONS:		libpcap - packet filtering library based on the BSD packet
--					filter (BPF)
--
--	DATE:			April 23, 2006
--
--	REVISIONS:		(Date and nic_description)
--
--	DESIGNERS:		Based on the code by Martin Casado & Richard Stevens
--					Modified & redesigned: Aman Abdulla: April 23, 2006
--
--	PROGRAMMER:		Aman Abdulla
--
--	NOTES:
--	The program illustrates the use of some basic pcap functions to capture 
-- 	a single packet.
---------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <pcap.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h>
#include <time.h> 

int main (int argc, char **argv)
{
		int max_len;
    	char *nic_dev; 
    	char errbuf[PCAP_ERRBUF_SIZE];
    	pcap_t* nic_descr;
    	const u_char *packet;
    	struct pcap_pkthdr pkt_hdr;     // defined in pcap.h 
    	struct ether_header *eptr;  // defined in net/ethernet.h 

    	u_char *ptr; /* printing out hardware header info */

    	// find the first NIC that is up and sniff packets from it
    	nic_dev = pcap_lookupdev (errbuf);

    	if (nic_dev == NULL)
    	{
        	printf("%s\n",errbuf);
        	exit(1);
    	}

    	printf ("DEV: %s\n", nic_dev);

    	// open the device for packet capture
		/*
       	pcap_t *pcap_open_live (	char *device,
				int snaplen, -	maximum size of packets to capture in bytes
				int prmisc,  -  put the card in promiscuous mode
				int to_ms,   -  Timeout waiting for packets
       				char *ebuf)  -  Error string is returned in this variable
		*/
       
  		nic_descr = pcap_open_live (nic_dev, BUFSIZ, 0, -1, errbuf);

    	if(nic_descr == NULL)
    	{
        	printf("pcap_open_live(): %s\n",errbuf);
        	exit(1);
    	}


    	// grab the packet from nic_descr using the following structure:

  		/*  
        struct pcap_pkthdr {
        	struct timeval ts;    time stamp 
        	bpf_u_int32 caplen;   length of portion present 
        	bpf_u_int32;          lebgth this packet (off wire) 
        }
     	*/

    	packet = pcap_next (nic_descr, &pkt_hdr);

    	if(packet == NULL)
    	{
        	printf("Could not capture a packet\n");
        	exit(1);
    	}

      	//Print out the header information
		printf("Packet length: %d\n",pkt_hdr.len);
    	printf("Capture Time: %s\n",ctime((const time_t*)&pkt_hdr.ts.tv_sec)); 
    	printf("Ethernet Address Length: %d\n",ETHER_HDR_LEN);

    	// Check header type
    	eptr = (struct ether_header *) packet;

    	// Check to see if it is an ip packet */
    	if (ntohs (eptr->ether_type) == ETHERTYPE_IP)
    	{
        	printf("Ethernet type hex:%x dec:%d is an IP packet\n",
                	ntohs(eptr->ether_type),
                	ntohs(eptr->ether_type));
    	}
		else  if (ntohs (eptr->ether_type) == ETHERTYPE_ARP)
    	{
        	printf("Ethernet type hex:%x dec:%d is an ARP packet\n",
                	ntohs(eptr->ether_type),
                	ntohs(eptr->ether_type));
    	}
		else 
		{
        	printf("Ethernet type %x not IP", ntohs(eptr->ether_type));
        	exit(1);
    	}

    	// Get the MAC addresses - from W. R. Stevens
    	ptr = eptr->ether_dhost;
    	max_len = ETHER_ADDR_LEN;
    	printf(" Destination Address:  ");
    	do
		{
        	printf("%s%x",(max_len == ETHER_ADDR_LEN) ? " " : ":",*ptr++);
    	}while (--max_len > 0);
    	printf("\n");

    	ptr = eptr->ether_shost;
    	max_len = ETHER_ADDR_LEN;
    	printf(" Source Address:  ");
    	do
		{
        	printf("%s%x",(max_len == ETHER_ADDR_LEN) ? " " : ":",*ptr++);
    	}while (--max_len > 0);
    	printf("\n");

    	return 0;
}
