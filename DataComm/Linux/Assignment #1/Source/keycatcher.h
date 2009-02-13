#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#ifndef _KEYCATCHER_H_

#define BUFFER_LEN 80 // The standard width of a terminal screen

#define ASCII_BS	0x7F
#define ASCII_CR	0x0D
#define ASCII_LF 	0x0A
#define ASCII_CTRL_K	0x0B
#define ASCII_ESC	0x1B

void input(int[], int[]);
void output(int[]);
void translate(int[], int[]);
void init_buffer(char[]);
void stty_io(int);
void fatal(char *);
void catch_sig(int);

#endif
