/*---------------------------------------------------------------------------------------------
--	SOURCE FILE:	pkt_sniffer.c -   A simple but complete packet capture 
--					program that will capture and parse packets
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
--	The program will selectively capture a specified number packets using a specified filter
--	The program will parse the headers and print out selected fields of interest.
-------------------------------------------------------------------------------------------------*/

#include <pcap.h>
#include <stdlib.h>
#include <netinet/ip.h> 
#include "pkt_sniffer.h"

// Function Prototypes
void pkt_callback (u_char*, const struct pcap_pkthdr*, const u_char*);

int main(int argc,char **argv)
{ 
		char *nic_dev; 
    	char errbuf[PCAP_ERRBUF_SIZE];
    	pcap_t* nic_descr;
    	struct bpf_program fp;      // holds compiled program     
    	bpf_u_int32 maskp;          // subnet mask               
    	bpf_u_int32 netp;           // ip                        
    	u_char* args = NULL;

    	// Options must be passed in as a string 
    	if (argc < 2)
		{ 
        	fprintf(stdout,"Usage: %s <Number of Packets> \"<Filter String>\"\n",argv[0]);
        	return 0;
    	}

		// find the first NIC that is up and sniff packets from it    	
		nic_dev = pcap_lookupdev(errbuf);
    	if (nic_dev == NULL)
    	{ 
			printf("%s\n",errbuf); 
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
		// set the device in promiscuous mode 
    	nic_descr = pcap_open_live (nic_dev, BUFSIZ, 1, -1, errbuf);
    	if (nic_descr == NULL)
    	{ 
			printf("pcap_open_live(): %s\n",errbuf); 
			exit(1); 
		}


    	if(argc > 2)
    	{
        	// Compile the filter expression
        	if (pcap_compile (nic_descr, &fp, argv[2], 0, netp) == -1)
        	{ 
				fprintf(stderr,"Error calling pcap_compile\n"); 
				exit(1);
			}

        	// Load the filter into the capture device
        	if (pcap_setfilter (nic_descr, &fp) == -1)
        	{ 
				fprintf(stderr,"Error setting filter\n"); 
				exit(1); 
			}
    	}

    	// Start the capture session 
    	pcap_loop (nic_descr, atoi(argv[1]), pkt_callback, args);

    	fprintf(stdout,"\nCapture Session Done\n");
    	return 0;
}

