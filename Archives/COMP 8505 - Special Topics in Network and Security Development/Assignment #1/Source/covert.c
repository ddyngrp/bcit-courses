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
 * FUNCTION:    main 
 * 
 * DATE:        May 17, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   int main(int argc, char **argv)
 *                  argc - argument count
 *                  argv - array of arguments
 * 
 * RETURNS:     Result on success or failure.
 *
 * NOTES: Main entry point into the program. Initializes command-line argument
 *        parsing as well as causing the program to enter into client or server
 *        mode.
 *
 *----------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{

	/* make sure user is root */
	if (geteuid() != USER_ROOT) {
		fprintf(stderr, "You must be root to run this program.\n");
		exit(ERROR_NOTROOT);
	}

	/* parse CLI options */
	if (parse_options(argc, argv) == OPTIONS_ERROR) {
		err(1, "Invalid options");
		exit(OPTIONS_ERROR);
	}

	print_settings(argv[0]);

	/* run as client/server */
	if (conn_info.mode_server == TRUE) {
		packet_decode();
	}
	else
		if (file_io(NULL) == ERROR_FILE) {
			err(1, "file_io");
			exit(ERROR_FILE);
		}

    return ERROR_NONE;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    print_settings
 * 
 * DATE:        May 17, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   void print_settings(char *command)
 *                   command - the program's name
 * 
 * RETURNS: void
 * 
 * NOTES: Prints out the current settings that are being used in the current
 *        run of the application.
 *
 *----------------------------------------------------------------------------*/
void print_settings(char *command)
{
	printf("Using the Following Options: (For help use \"%s -h\")\n", command);
	if (conn_info.mode_server == TRUE)
		printf("  Running as server:       TRUE\n");
	else
		printf("  Running as client:       TRUE\n");
	printf("  Destination IP address:  %s\n", conn_info.dest_ip);
	printf("  Destination port:        %d\n", conn_info.dest_port);
	printf("  Window size:             %d\n", conn_info.th_win);

	if (conn_info.mode_server == TRUE)
		printf("  Output to File:          %s\n\n", conn_info.file_name);
	else
		printf("  Input from File:         %s\n\n", conn_info.file_name);
	
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    print_usage
 * 
 * DATE:        May 18, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   void print_usage(char *command, int err)
 *                   command - the program's name
 *                   err - error produced
 * 
 * RETURNS: void
 * 
 * NOTES: Prints out the program's useage information if the user incorrectly
 *        entered an option or used the -h or --help option.
 *
 *----------------------------------------------------------------------------*/
void print_usage(char *command, int err)
{
    if (err == OPTIONS_HELP) {
        printf("usage: %s [arguments]\n\n", command);
        printf("Arguments:\n");
        printf("  -s  or  --server       Run as server, otherwise as client\n");
        printf("  -d  or  --dest-ip      Destination IP address\n");
        printf("  -p  or  --dest-port    Destination port\n");
        printf("  -w  or  --window-size  Window size (server/client must agree)\n");
        printf("  -f  or  --file         File to read from or write to\n");
        printf("  -h  or  --help         Prints out this screen\n");
		exit(OPTIONS_HELP);
    }
	else if (err == OPTIONS_ERROR)
        printf("Try `%s --help` for more information.\n", command);
	else {
        printf("%s: unknown error\n", command);
        printf("Try `%s --help` for more information.\n", command);
    }	
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    parse_options 
 * 
 * DATE:        May 17, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   parse_options(int argc, char *argv[])
 *                    argc - argument count
 *                    argv - argument list
 * 
 * RETURNS:     ERROR_NONE on success OPTIONS_ERROR on failure.
 * 
 * NOTES: Sets default options and parses any command-line options.
 *
 *----------------------------------------------------------------------------*/
int parse_options(int argc, char *argv[])
{
	int c, option_index = 0;

	static struct option long_options[] =
	{
		{"server"		, no_argument		, 0, 's'},
		{"dest-ip"		, required_argument	, 0, 'd'},
		{"dest-port"	, required_argument	, 0, 'p'},
		{"window-size"	, required_argument	, 0, 'w'},
		{"file"			, required_argument	, 0, 'f'},
		{"help"			, no_argument		, 0, 'h'},
		{0, 0, 0, 0}
	};

	/* set defaults */
	conn_info.mode_server = FALSE;
	conn_info.dest_ip = "192.168.1.1";
	conn_info.dest_port = 3141;
	conn_info.th_win = 31415;
	conn_info.file_name = "./INSTALL";

	/* parse options */
	while (TRUE) {
		c = getopt_long(argc, argv, "sd:p:w:f:h", long_options, &option_index);

		if (c == -1)
			break;

		switch (c) {
			case 0:
				if (long_options[option_index].flag != 0)
					break;
				break;

			case 's':
				conn_info.mode_server = TRUE;
				break;

			case 'd':
				conn_info.dest_ip = optarg;
				break;

			case 'p':
				if (atoi(optarg) > 0)
					conn_info.dest_port = atoi(optarg);
				else {
					print_usage(argv[0], OPTIONS_ERROR);
					return OPTIONS_ERROR;
				}
				break;

			case 'w':
				if (atoi(optarg) > 0)
					conn_info.th_win = atoi(optarg);
				else {
					print_usage(argv[0], OPTIONS_ERROR);
					return OPTIONS_ERROR;
				}
				break;

			case 'f':
				conn_info.file_name = optarg;
				break;

			case 'h':
				print_usage(argv[0], OPTIONS_HELP);
				break;			

			default:
				print_usage(argv[0], OPTIONS_ERROR);
				return OPTIONS_ERROR;
				break;
		}
	}

	return ERROR_NONE;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    file_io
 * 
 * DATE:        May 17, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   file_io(char *recv_buffer)
 *                   recv_buffer - buffer to be saved to disk 
 * 
 * RETURNS:     ERROR_NONE on success, ERROR_FILE on failure.
 * 
 * NOTES: If running as a server and recv_buffer is not null, this function
 *        goes into write mode. Otherwise, running as a client, this function
 *        reads a file 32 bits at a time and sends each chunk over a raw socket
 *        as part of the source IP field.
 *
 *----------------------------------------------------------------------------*/
int file_io(char *recv_buffer)
{
	FILE *file;
	char buffer[BUFFER_SIZE + 1];
	char ip_addr[16];
	int file_size;
	int	read_bytes;
	int file_position = 0;
	struct in_addr addr;

	/* determine if we are reading or writing */
	if (recv_buffer == NULL) { /* client sends file */
		if ((file = fopen(conn_info.file_name, "rb")) == NULL)
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
	else { /* server receives file */
		if ((file = fopen(conn_info.file_name, "a+")) == NULL)
			return ERROR_FILE;

		fprintf(file, "%s", recv_buffer);

		fclose(file);
	}

	return ERROR_NONE;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    packet_forge
 * 
 * DATE:        May 17, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   packet_forge(unsigned int source_addr)
 *                    source_addr - the address being forged into the packet.
 * 
 * RETURNS:     void
 * 
 * NOTES: Sends data over a raw socket encoded into the source IP field.
 *
 *----------------------------------------------------------------------------*/
void packet_forge(unsigned int source_addr)
{
	struct ip iph;
	struct tcphdr tcph;
	struct sockaddr_in sin;
	struct timeval time;
	unsigned char *packet;
	const int on = 1;
	int sock_fd, send_len;

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
	iph.ip_dst.s_addr = inet_addr(conn_info.dest_ip);

	/* create a forged TCP header */
	tcph.th_sport = htons(1 + (int)(10000.0 * rand() / (RAND_MAX + 1.0)));
	tcph.th_dport = htons(conn_info.dest_port);
	tcph.th_seq = htonl(1 + (int)(10000.0 * rand() / (RAND_MAX + 1.0)));
	tcph.th_off = sizeof(struct tcphdr) / 4;
	tcph.th_flags = TH_SYN;
	tcph.th_win = htons(conn_info.th_win);
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
	memcpy(packet, &iph, sizeof(iph));
	memcpy(packet + sizeof(iph), &tcph, sizeof(tcph));

	/* send the packet */
	if ((send_len = sendto(sock_fd, packet, 60, 0,
					(struct sockaddr *)&sin,
					sizeof(struct sockaddr))) < ERROR_NONE) {
		err(1, "sendto");
		exit(ERROR_SEND);
	}

	printf("Sending Data: %s\t = %s\n", inet_ntoa(iph.ip_src),
			ip_to_string(iph.ip_src));

	close(sock_fd);
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    packet_decode
 * 
 * DATE:        May 17, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   packet_decode(void)
 * 
 * RETURNS:     void
 * 
 * NOTES: Decodes incoming packets that have a specified window setting.
 *        Additionally decodes the forged source IP address into a string to be
 *        written to disk.
 *
 *----------------------------------------------------------------------------*/
void packet_decode()
{
	struct recv_tcp {
		struct ip iph;
		struct tcphdr tcph;
		char buffer[BUFFER_RECV];
	} recv_pkt;

	int sock_fd, recv_len;

	while(TRUE) { /* read packet loop */
		/* open socket for reading */

		if ((sock_fd = socket(AF_INET, SOCK_RAW, 6)) < ERROR_NONE) {
			err(1, "socket");
			exit(ERROR_SOCKET);
		}

		/* listen for data */
		if ((recv_len = read(sock_fd, (struct recv_tcp *)&recv_pkt,
						BUFFER_RECV)) < ERROR_NONE) {
			err(1, "read");
			exit(ERROR_READ);
		}

		/* if the packet has SYN/ACK flag and a window size of TCP_WINDOW */
		if ((recv_pkt.tcph.th_flags == TH_SYN)
				&& (ntohs(recv_pkt.tcph.th_win) == conn_info.th_win)) {

			printf("Receiving Data: %s\n", ip_to_string(recv_pkt.iph.ip_src));
			if (file_io(ip_to_string(recv_pkt.iph.ip_src)) == ERROR_FILE) {
				err(1, "file_io");
				exit(ERROR_FILE);
			}
		}

		close(sock_fd);
	}
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
 * INTERFACE:   in_cksum(unsigned short *addr, int len)
 *                     addr - the IP to be checksummed
 *                     len - lengh of the header
 * 
 * RETURNS:     A checksum on the IP header.
 * 
 * NOTES: Creates a valid checksum for an IP header.
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
 * INTERFACE:   in_cksum_tcp(int src, int dst, unsigned short *addr, int len)
 *                   src - source IP address
 *                   dst - destination IP address
 *                   addr - TCP header
 *                   len - length of TCP header
 * 
 * RETURNS:     Valid checksum on TCP header
 * 
 * NOTES: Creates a valid TCP checksum.
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

/*-----------------------------------------------------------------------------
 * FUNCTION:    ip_to_string
 * 
 * DATE:        May 17, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   ip_to_string(struct in_addr addr)
 *                   addr - struct to hold IP address info
 * 
 * RETURNS:     Decoded string
 * 
 * NOTES: Splits an IP address up into 4 parts, each 8 bytes or 1 char per
 *        section and the returns the 32-bit string to the calling function.
 *
 *----------------------------------------------------------------------------*/
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
