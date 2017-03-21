#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <termios.h>

typedef unsigned char			BYTE;
typedef unsigned short			WORD;
typedef signed int			LONG;
typedef unsigned int			DWORD;

typedef struct tagCOMM_ATTR
 {
	DWORD	baudrate;		
	BYTE	databits;
	BYTE	parity;
	BYTE	stopbits;	
	BYTE	reserved;
} COMM_ATTR;


enum comm_stopbits_t 
{
	COMM_ONESTOPBIT,
	COMM_ONE5STOPBITS,
	COMM_TWOSTOPBITS,
};

enum comm_parity_t 
{
	COMM_NOPARITY,
	COMM_ODDPARITY,
	COMM_EVENPARITY,
	COMM_MARK,
	COMM_SPACE,
};


#define COMM_PURGE_TXABORT			0x0001	
#define COMM_PURGE_RXABORT			0x0002	
#define COMM_PURGE_TXCLEAR			0x0004	
#define COMM_PURGE_RXCLEAR			0x0008	


#define MAX(a, b)		(a > b? a: b)

#define ERR_PRINT		perror
#define LIBDVR_PRINT		printf

char *DEV_COM_RFID = NULL;
char *DEV_COM_GPRS = NULL;


int CommOpen(char *DEV_COM);

int CommDestory(int fd);

int SetAttribute(int fd,COMM_ATTR *pattr);

int GetAttribute(int fd);

int CommRead(int fd,void *pdata, DWORD nbytes);

int CommWrite(int fd,void *pdata, DWORD len);

int CommPurge(int fd,DWORD dw_flags);

void rfid(int fd);

int  rfid_init(void);

int gprs_init(void);
