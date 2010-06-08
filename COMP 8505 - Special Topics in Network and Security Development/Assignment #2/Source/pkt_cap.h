/*-----------------------------------------------------------------------------
 * pkt_cap.h - Linux backdoor packet capture
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

#ifndef PKT_CAP_H
#define PKT_CAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include <pcap.h>

#define __FAVOR_BSD	/* use BSD-style headers */
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <arpa/inet.h>

/* defaults */
#define MAX_PKT_LEN			1518	/* maximum bytes per packet to capture */
#define ETHERNET_SIZE		14		/* ethernet header size */
#define ETHERNET_ADDR_LEN	6		/* ethernet address length */

/* ethernet header */
struct pcap_ethernet {
	unsigned char	ether_dhost[ETHERNET_ADDR_LEN];	/* destination host address */
	unsigned char	ether_shost[ETHERNET_ADDR_LEN];	/* source host address */
	unsigned short	ether_type;						/* IP? ARP? RARP? etc */
};

/* IP header */
struct pcap_ip {
	unsigned char		ip_vhl;			/* version << 4 | header length >> 2 */
	unsigned char		ip_tos;			/* type of service */
	unsigned short		ip_len;			/* total length */
	unsigned short		ip_id;			/* identification */
	unsigned short		ip_off;			/* fragment offset field */
	#define IP_RF		0x8000			/* reserved fragment flag */
	#define IP_DF		0x4000			/* dont fragment flag */
	#define IP_MF		0x2000			/* more fragments flag */
	#define IP_OFFMASK	0x1fff			/* mask for fragmenting bits */
	unsigned char		ip_ttl;			/* time to live */
	unsigned char		ip_p;			/* protocol */
	unsigned short		ip_sum;			/* checksum */
	struct in_addr		ip_src, ip_dst;	/* source and dest address */
};

/* useful IP header macros */
#define IP_HL(ip)	(((ip)->ip_vhl) & 0x0f)
#define IP_V(ip)	(((ip)->ip_vhl) >> 4)

/* TCP header */
typedef unsigned int tcp_seq;

struct pcap_tcp {
	unsigned short		th_sport;	/* source port */
	unsigned short		th_dport;	/* destination port */
	tcp_seq				th_seq;		/* sequence number */
	tcp_seq				th_ack;		/* acknowledgement number */
	unsigned char		th_offx2;	/* data offset, reserved */
	#define TH_OFF(th)	(((th)->th_offx2 & 0xf0) >> 4)
	unsigned char  th_flags;
	#define TH_FIN		0x01		/* fin */
	#define TH_SYN		0x02		/* syn */
	#define TH_RST		0x04		/* reset */
	#define TH_PUSH		0x08		/* push */
	#define TH_ACK		0x10		/* ack */
	#define TH_URG		0x20		/* urgent */
	#define TH_ECE		0x40		/* ECN Echo (ECE) */
	#define TH_CWR		0x80		/* reduced (CWR) */
	#define TH_FLAGS	(TH_FIN|TH_SYN|TH_RST|TH_ACK|TH_URG|TH_ECE|TH_CWR)
	unsigned short		th_win;		/* window */
	unsigned short		th_sum;		/* checksum */
	unsigned short		th_urp;		/* urgent pointer */
};

/* function prototypes */
void packet_callback(unsigned char *, const struct pcap_pkthdr *, const unsigned char *);
void print_payload(const unsigned char *, int);
void print_hex_line(const unsigned char *, int, int);

#endif
