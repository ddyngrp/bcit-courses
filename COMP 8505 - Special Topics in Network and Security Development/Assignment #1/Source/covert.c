/*-----------------------------------------------------------------------------
 * covert.c - Covert communication over TCP/IP
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

#include "covert.h"

/*-----------------------------------------------------------------------------
 * FUNCTION:    
 * 
 * DATE:        May 17, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   
 * 
 * RETURNS:     
 * 
 * NOTES: 
 *
 *----------------------------------------------------------------------------*/
int main (int argc, const char *argv[])
{

	/* make sure user is root */
	if (geteuid() != USER_ROOT) {
		fprintf(stderr, "You must be root to run this program.\n");
		exit(ERROR_NOTROOT);
	}

	/* parse CLI options */
	if (argc == 1)
		print_usage();
	else
		if (parse_options(argc, argv) == ERROR_OPTIONS) {
			err(1, "Invalid options");
			print_usage();
			exit(ERROR_OPTIONS);
		}

	print_settings();

    return ERROR_NONE;
}

void print_settings()
{
}

void print_usage()
{
}

int parse_options(int argc, const char *argv[])
{
	return ERROR_NONE;
}

int file_io(char *file_name, char *recv_buffer)
{
	FILE *file;
	char buffer[BUFFER_SIZE + 1];
	char ip_addr[16];
	int file_size;
	int	read_bytes;
	int file_position = 0;
	struct in_addr addr;

	/* determine if we are reading or writing */
	if (recv_buffer == NULL) { /* server sends file */
		if ((file = fopen(file_name, "rb")) == NULL)
			return ERROR_FILE;
		else {
			fseek(file, 0, SEEK_END);
			file_size = ftell(file);
			rewind(file);

			/* accumulate 32 bits of data, which is the length
			 * of the source addresss */
			while (file_position < file_size) {
				/* read 32 bits and place in source address buffer */
				read_bytes = fread(buffer, sizeof(char), BUFFER_SIZE, file);

				file_position += read_bytes;

				sprintf(ip_addr, "%d.%d.%d.%d", buffer[0], buffer[1],
						buffer[2], buffer[3]);

				inet_aton(ip_addr, &addr);

				packet_forge(addr.s_addr); /* send the packet */
				usleep(DELAY_USEC); /* give the packet time to get there */

				memset(&buffer, '\0', sizeof(buffer)); /* clear the buffer */
			}
		}

		fclose(file);
	}
	else if (recv_buffer != NULL) { /* client receives file */
	}

	return ERROR_NONE;
}

void packet_forge(unsigned int source_addr)
{
	struct ip iph;
	struct tcphdr tcph;
	struct sockaddr_in sin;
	struct timeval time;
	unsigned char *packet;
	const int on = 1;
	int sock_fd;

	/* seed random number generator */
	gettimeofday(&time, NULL);
	srand(time.tv_usec);

	/* allocate memory for the packet */
	packet = (unsigned char *)malloc(60);

	/* create a forged IP header */
	iph.ip_hl	= 0x5;
	iph.ip_v	= 0x4;
	iph.ip_tos	= 0x0;
	iph.ip_len	= sizeof(struct ip) + sizeof(struct tcphdr);
	iph.ip_id	= htonl((int)(255.0 * rand() / (RAND_MAX + 1.0)));
	iph.ip_off	= 0x0;
	iph.ip_ttl	= 0x64;
	iph.ip_sum	= 0;
	iph.ip_p	= IPPROTO_TCP;
	iph.ip_src.s_addr = source_addr;
	iph.ip_dst.s_addr = inet_addr("192.168.1.1");

	/* create a forged TCP header */
	tcph.th_sport = htons(1 + (int)(10000.0 * rand() / (RAND_MAX + 1.0)));
	tcph.th_dport = htons(conn_info.dest_port);
	tcph.th_seq = htonl(1 + (int)(10000.0 * rand() / (RAND_MAX + 1.0)));
	tcph.th_off = sizeof(struct tcphdr) / 4;
	tcph.th_flags = TH_SYN;
	tcph.th_win = htons(32768);
	tcph.th_sum = 0;

	/* combine the forged headers into a socket struct */
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = iph.ip_dst.s_addr;

	/* open raw socket for sending */
	if ((sock_fd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) < ERROR_NONE) {
		err(1, "socket");
		exit(ERROR_SOCKET);
	}

	if (setsockopt(sock_fd, IPPROTO_IP, IP_HDRINCL, &on, sizeof(on)) < ERROR_NONE) {
		err(1, "setsockopt");
		exit(ERROR_SOCKET);
	}	

	/* create checksums */
	iph.ip_sum = in_cksum((unsigned short*)&iph, sizeof(iph));
	tcph.th_sum = in_cksum_tcp(iph.ip_src.s_addr, iph.ip_dst.s_addr,
			(unsigned short *)&tcph, sizeof(tcph));

	/* finish full header */
	memcpy(packet, &iph, sizeof(iph)); /* copy IP header to beginning of packet */
	memcpy(packet + sizeof(iph), &tcph, sizeof(tcph)); /* copy TCP header to offset 20 */

	/* send the packet */
	sendto(sock_fd, packet, 60, 0, (struct sockaddr *)&sin, sizeof(struct sockaddr));

	printf("Sending Data: %s\t = %s\n", inet_ntoa(iph.ip_src),
			ip_to_string(iph.ip_src));

	close(sock_fd);
}

void packet_decode()
{
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    in_cksum
 * 
 * DATE:        May 17, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    W. Richard Stevens (From UNIX Network Programming)
 * 
 * PROGRAMMER:  W. Richard Stevens (From UNIX Network Programming)
 * 
 * INTERFACE:   
 * 
 * RETURNS:     
 * 
 * NOTES: 
 *
 *----------------------------------------------------------------------------*/
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

/*-----------------------------------------------------------------------------
 * FUNCTION:    in_cksum_tcp
 * 
 * DATE:        May 17, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Murat Balaban <murat@enderunix.org>
 * 
 * PROGRAMMER:  Murat Balaban <murat@enderunix.org>
 * 
 * INTERFACE:   
 * 
 * RETURNS:     
 * 
 * NOTES: 
 *
 *----------------------------------------------------------------------------*/
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

char *ip_to_string(struct in_addr addr)
{
	char *ip_str = inet_ntoa(addr);
	char *data = malloc((BUFFER_SIZE + 1) * sizeof(char));
	int i;

	data[0] = atoi(strtok(ip_str, "."));

	for (i = 1; i < BUFFER_SIZE; i++) {
		data[i] = atoi(strtok(NULL, "."));
	}

	return data;
}
