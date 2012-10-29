#include <windows.h>

// packet size constraints
#define PACKET_LENGTH_MIN	255	// data section == 
#define PACKET_LENGTH_MAX	8	// no data section
#define PACKET_CMD1_MIN		0x01
#define PACKET_CMD1_MAX		0x60
#define PACKET_CMD2_MIN		0x61
#define PACKET_CMD2_MAX		0xFF

// valid packet value requirements
#define DEV_ID		0x03
#define SOF			0x01

// packet byte indices
#define PACKET_SOF		0
#define PACKET_LSB		1
#define PACKET_MSB		2
#define PACKET_DEV_ID	3
#define PACKET_CMD1		4
#define PACKET_CMD2		5
#define PACKET_DATA1	6
#define PACKET_DATAN(x)	x-3
#define PACKET_LRC1(x)	x-2
#define PACKET_LRC2(x)	x-1

// section lenghts
#define PACKET_DATA_LENGTH(x)	x - PACKET_LENGTH_MIN


#define CMD2_ENTER_DOWNLOAD_MODE	0x20
#define CMD2_GET_VERSION			0x40
#define CMD2_FIND_TOKEN				0x41
#define CMD2_TOKEN_PRIORITY			0x42
#define CMD2_SET_DRIVER				0x43
#define CMD2_PASS_THROUGH			0x45
#define CMD2_SET_BAUD_RATE			0x46
#define CMD2_TRANSMITTER_ON			0x48
#define CMD2_TRANSMITTER_OFF		0x49

int parse_packet(char *packet, size_t len);
int interpret_cmd(char cmd1, char cmd2, char *packet, size_t len);
int check_common_errors(int cmd1, int cmd2, char *data, size_t len);
int validate_packet(char *packet, size_t len);
int lrc(const char* s, size_t len);
