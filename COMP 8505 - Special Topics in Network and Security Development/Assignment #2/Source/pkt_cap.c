/*-----------------------------------------------------------------------------
 * pkt_cap.c - Linux backdoor packet capture
 * Copyright (C) 2010 Steffen L. Norgren <ironix@trollop.org>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *----------------------------------------------------------------------------*/

#include "pkt_cap.h"

/*-----------------------------------------------------------------------------
 * FUNCTION:    print_hex_line
 * 
 * DATE:        June 4, 2010
 * 
 * DESIGNER:    The Tcpdump Group <http://www.tcpdump.org/>
 * 
 * PROGRAMMER:  The Tcpdump Group <http://www.tcpdump.org/>
 * 
 * INTERFACE:   print_hex_line(const unsigned char *payload, int len, int offset)
 *                   payload - payload data
 *                   len - length of payload
 *                   offset - current offset
 * 
 * RETURNS:     void
 * 
 * NOTES: Prints packet payload data as HEX
 * 00000   47 45 54 20 2f 20 48 54  54 50 2f 31 2e 31 0d 0a   GET / HTTP/1.1..
 *
 *----------------------------------------------------------------------------*/
void print_hex_line(const unsigned char *payload, int len, int offset)
{
	int i, gap;
	const unsigned char *ch;

	/* offset */
	printf("%05d   ", offset);

	/* HEX */
	ch = payload;
	for(i = 0; i < len; i++) {
		printf("%02x ", *ch);
		ch++;
		/* print extra space after 8th byte for visual aid */
		if (i == 7)
			printf(" ");
	}

	/* print space to handle line less than 8 bytes */
	if (len < 8)
		printf(" ");

	/* fill HEX gap with spaces if not full line */
	if (len < 16) {
		gap = 16 - len;
		for (i = 0; i < gap; i++) {
			printf("   ");
		}
	}

	/* space before ASCII printout */
	printf("   ");

	/* ASCII */
	ch = payload;
	for(i = 0; i < len; i++) {
		if (isprint(*ch)) /* only print if printable */
			printf("%c", *ch);
		else
			printf(".");
		ch++;
	}

	printf("\n");

	return;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    print_payload
 * 
 * DATE:        June 4, 2010
 * 
 * DESIGNER:    The Tcpdump Group <http://www.tcpdump.org/>
 * 
 * PROGRAMMER:  The Tcpdump Group <http://www.tcpdump.org/>
 * 
 * INTERFACE:   print_payload(const unsigned char *payload, int len)
 *                   payload - payload data
 *                   len - length of payload
 * 
 * RETURNS:     void
 * 
 * NOTES: Prints packet payload data and avoids outputting binary data
 *
 *----------------------------------------------------------------------------*/
void print_payload(const unsigned char *payload, int len)
{

	int len_rem = len;
	int line_width = 16;	/* number of bytes per line */
	int line_len;
	int offset = 0;			/* zero-based offset counter */
	const unsigned char *ch = payload;

	if (len <= 0)
		return;

	/* data fits on one line */
	if (len <= line_width) {
		print_hex_line(ch, len, offset);
		return;
	}

	/* data spans multiple lines */
	for (;;) {
		line_len = line_width % len_rem;		/* compute line length */
		print_hex_line(ch, line_len, offset);	/* print line */
		len_rem = len_rem - line_len;			/* compute remaining */
		ch = ch + line_len;						/* shift pointer to remianing bytes */
		offset = offset + line_width;			/* add offset */

		/* check if we have line width chars or less */
		if (len_rem <= line_width) {
			print_hex_line(ch, len_rem, offset);/* print last line */
			break;
		}
	}

	return;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    packet_callback
 * 
 * DATE:        June 4, 2010
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   packet_callback(unsigned char *args,
 *                              const struct pcap_pkthdr *header,
 *                              const unsigned char *packet)
 *                   args - arguments passed by loop
 *                   header - the packet header
 *                   packet - user data (packet payload)
 * 
 * RETURNS:     void
 * 
 * NOTES: Callback for handling sniffed packets.
 *
 *----------------------------------------------------------------------------*/
void packet_callback(unsigned char *args, const struct pcap_pkthdr *pkt_header,
		const unsigned char *packet)
{
	static int count = 1;	/* packet counter */

	/* declare pointers to packet headers */
	const struct pcap_ethernet *ethernet;	/* The ethernet header [1] */
	const struct pcap_ip *ip;				/* The IP header */
	const struct pcap_tcp *tcp;				/* The TCP header */
	const unsigned char *payload;			/* Packet payload */

	int size_ip;
	int size_tcp;
	int size_payload;

	/* define ethernet header */
	ethernet = (struct pcap_ethernet*)(packet);

	/* define/compute ip header offset */
	ip = (struct pcap_ip*)(packet + ETHERNET_SIZE);
	size_ip = IP_HL(ip)*4;
	if (size_ip < 20) {
		printf("   * Invalid IP header length: %u bytes\n", size_ip);
		return;
	}

	/* print current packet number */
	printf("\nPacket #%d:\n", count++);

	/* print source and destination IP addresses */
	printf("       From: %s\n", inet_ntoa(ip->ip_src));
	printf("         To: %s\n", inet_ntoa(ip->ip_dst));

	/* determine and print protocol */	
	switch(ip->ip_p) {
		case IPPROTO_TCP:
			printf("   Protocol: TCP\n");
			break;
		case IPPROTO_UDP:
			printf("   Protocol: UDP\n");
			return;
		case IPPROTO_ICMP:
			printf("   Protocol: ICMP\n");
			return;
		case IPPROTO_IP:
			printf("   Protocol: IP\n");
			return;
		default:
			printf("   Protocol: unknown\n");
			return;
	}

	/*
	 *  OK, this packet is TCP.
	 */

	/* define/compute tcp header offset */
	tcp = (struct pcap_tcp*)(packet + ETHERNET_SIZE + size_ip);
	size_tcp = TH_OFF(tcp)*4;
	if (size_tcp < 20) {
		printf("   * Invalid TCP header length: %u bytes\n", size_tcp);
		return;
	}

	printf("   Src port: %d\n", ntohs(tcp->th_sport));
	printf("   Dst port: %d\n", ntohs(tcp->th_dport));

	/* define/compute tcp payload (segment) offset */
	payload = (unsigned char *)(packet + ETHERNET_SIZE + size_ip + size_tcp);

	/* compute tcp payload (segment) size */
	size_payload = ntohs(ip->ip_len) - (size_ip + size_tcp);

	/* print payload data as HEX */
	if (size_payload > 0) {
		printf("   Payload (%d bytes):\n", size_payload);
		print_payload(payload, size_payload);
	}

	return;
}
