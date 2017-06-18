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

#define BITS_DATA_5 5
#define BITS_DATA_6 6
#define BITS_DATA_7 7
#define BITS_DATA_8 8

typedef unsigned char  BYTE;
typedef unsigned short WORD;
typedef unsigned int   DWORD;
typedef signed int     LONG;


typedef struct serial_attr{
	unsigned int baudrate;
	unsigned char databits;
	unsigned char stopbits;
	unsigned char parity;
}serial_attr;


int serial_open(const char *DEV);
int set_serial_attr(int fd, serial_attr *attr);
int serial_read(int fd, char *rbuff, unsigned int nbytes);
int serial_write(int fd, char *wbuff, unsigned int nbytes);
int serial_close(int fd);
int serial_flushio(int fd);


#endif
