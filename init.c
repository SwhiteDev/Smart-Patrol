#include "init.h"


/**************************************************
 *函数名：rfid_init()
 *功  能：初始化rfid模块接口
 *参  数：void
 *返回值：int
**************************************************/
int rfid_init(void)
{
	const char *dev = "/dev/ttyUSB0";
	int fd = com_open(dev);
	com_attr attr = {0};
	attr.baudrate = 19200;
	attr.databits = 8;
	attr.parity = COMM_NOPARITY;
	attr.stopbits = COMM_ONESTOPBIT;
	if(set_com_attr(fd,&attr) != 0)
		printf("set com_rfid attr failed\n");
	get_com_attr(fd);
	return fd;
}
