#ifndef SERIAL_H
#define SERIAL_H
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <termios.h>


#define BITS_PARITY_NONE 0
#define BITS_PARITY_ODD 1
#define BITS_PARITY_EVEN 2

#define BITS_STOP_1 1
#define BITS_STOP_2 2


typedef unsigned char  BYTE;
typedef unsigned short WORD;
typedef unsigned int   DWORD;
typedef signed int     LONG;


typedef struct serial_attr{
	uint32_t baudrate;
	uint8_t  databits;
	uint8_t  stopbits;
	uint8_t  parity;
}serial_attr;


int serial_open(const char *DEV);
int set_serial_attr(int fd, serial_attr *attr);
int serial_read(int fd, BYTE *rbuff, uint32_t nbytes);
int serial_write(int fd, BYTE *wbuff, uint32_t nbytes);
int serial_close(int fd);
int serial_flushio(int fd);


#endif
