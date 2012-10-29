#include <windows.h>

#define ID_APPLICATION_LAYER_FIRMWARE 0x01
#define ID_14443A	0x02
#define ID_14443B	0x03
#define ID_15693	0x04
#define ID_TAGIT	0x05
#define ID_LFDST	0x06
#define ID_APOLLO	0x07
#define ID_14434	0x08	// unknown actual valued, guess :p
#define ID_BOOTLOADER_FIRWMARE	0x11

// error values
#define ERROR_NONE								0x00
#define ERROR_TOKEN_NOT_PRESENT					0x01

int received_get_version(char *data, size_t len);
int received_find_token(char *data, size_t len);
int received_token_priority(char *data, size_t len);
int received_set_driver(char *data, size_t len);
int received_set_baud_rate(char *data, size_t len);
int received_set_transmitter(int status, int id, char *data, size_t len);
