/*---------------------------------------------------------------------------------------
--	SOURCE FILE:	pkt_cap3.c -   A simple packet capture program
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
--	The program extends the previous examples by using the pcap_compile() and 
-- 	pcap_setfilter() functions to selectively capture packets of interest. 
---------------------------------------------------------------------------------------*/

#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h> 

// Function Prototypes
void pkt_callback (u_char*, const struct pcap_pkthdr*, const u_char*);


int main(int argc,char **argv)
{ 
    	char *nic_dev; 
    	char errbuf[PCAP_ERRBUF_SIZE];
    	pcap_t* nic_descr;
    	const u_char *packet;
    	struct pcap_pkthdr hdr;     // pcap.h                    
    	struct ether_header *eptr;  // net/ethernet.h            
    	struct bpf_program fp;      // holds the compiled program     
    	bpf_u_int32 maskp;          // subnet mask               
    	bpf_u_int32 netp;           // ip                        


    	if(argc != 2)
		{ 
			fprintf(stdout,"Usage: %s \"filter program\"\n", argv[0]);
			return 0;
		}

    	// find the first NIC that is up and sniff packets from it
    	nic_dev = pcap_lookupdev(errbuf);
    	if(nic_dev == NULL)
    	{ 
			fprintf(stderr,"%s\n",errbuf); 
			exit(1); 
		}

    	// Use pcap to get the IP address and subnet mask of the device 
    	pcap_lookupnet (nic_dev, &netp, &maskp, errbuf);


		// open the device for packet capture
		/*
       	pcap_t *pcap_open_live (char *device,
			i	nt snaplen, -	maximum size of packets to capture in bytes
				int prmisc,  -  put the card in promiscuous mode
				int to_ms,   -  Timeout waiting for packets
       				char *ebuf)  -  Error string is returned in this variable 
		*/					
		// open device for reading 
    	
		// set the device in promiscuous mode 
    	nic_descr = pcap_open_live (nic_dev, BUFSIZ, 1, -1, errbuf);
    	if (nic_descr == NULL)
    	{ 
			printf("pcap_open_live(): %s\n",errbuf); 
			exit(1); 
		}

    	// Compile the filter expression
    	if(pcap_compile (nic_descr, &fp, argv[1], 0, netp) == -1)
    	{ 
			fprintf(stderr,"Error calling pcap_compile\n"); 
			exit(1); 
		}

    	// Load the filter into the capture device
    	if (pcap_setfilter(nic_descr, &fp) == -1)
    	{ 
			fprintf(stderr,"Error setting filter\n"); 
			exit(1); 
		}

    	// Start the capture session 
    	pcap_loop (nic_descr, -1, pkt_callback, NULL);

    	return 0;
}

// This is the callback function that is passed to pcap_loop(..) and called each time 
// a packet is received                                                    */

void pkt_callback(u_char *ptr_null, const struct pcap_pkthdr* pkthdr, const u_char* packet)
{
		static int count = 1;
		fprintf(stdout,"%d = %s\n", count, packet);
    	fflush(stdout);
    	count++;
}

