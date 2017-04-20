#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <termios.h>
                                   
#define FALSE -1
#define TRUE 0

#define COMM_NOPARITY 0             /*无校验位、奇校验、偶校验*/
#define COMM_ODDPARITY 1            
#define COMM_EVENPARITY 2           
             
#define COMM_ONESTOPBIT 1     /*停止位*/
#define COMM_TWOSTOPBITS 2   


typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef signed int LONG;
typedef unsigned int DWORD;

typedef struct com_attr       /*串口属性结构*/         
{
	unsigned int baudrate;    /*波特率*/
	unsigned char databits;    /*数据位*/
	unsigned char stopbits;    /*停止位*/
	unsigned char parity;    /*校验位*/
}com_attr;


int  com_open(const char *dev);   
int  set_com_attr(int fd, com_attr *attr);  /*设置串口属性*/
void get_com_attr(int fd);    /*获取串口属性*/
int  com_read(int fd, BYTE *rbuff, DWORD nbytes);
int  com_write(int fd, BYTE *wbuff, DWORD nbytes);
void com_close(int fd);

int rfid(int fd);
void gprs(int fd);

int rfid_init();
int gprs_init();

void card_to_post(unsigned char card[]);    //卡号填充
