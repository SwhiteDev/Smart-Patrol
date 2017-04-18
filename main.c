#include "mycom.h"
DWORD num = 512;
extern BYTE rbuff[512];
extern BYTE wbuff[512];


int main()
{
	int rfid_fd = -1;
	rfid_fd = rfid_init();
	while(1)
	{
	rfid(rfid_fd);
	}
//	int gprs_fd = gprs_init();
	return 0;
}

/**************************************************
 *函数名：gprs_init()
 *功  能：初始化gprs模块接口，与服务器建立tcp链接
 *参  数：void
 *返回值：int
**************************************************/
/*int gprs_init(void)
{
	DEV_COM_GPRS = "/dev/ttyUSB1";
	int fd = CommOpen(DEV_COM_GPRS);
	COMM_ATTR attr = {0};
	attr.baudrate = 9600;
	attr.databits = 8;
	attr.parity = COMM_NOPARITY;
	attr.stopbits = COMM_ONESTOPBIT;
	if(SetAttribute(fd,&attr) != 0)
		printf("set com_gprs attr failed\n");
	GetAttribute(fd);
	//初始化SIM卡相关AT指令
	char *cmd[] = {"AT\r",                 \
			"AT+CCID\r"};
	int ret_w;
	ret_w = write(fd,cmd[1],(sizeof(cmd[1])-1));
	sleep(2);//
	int ret_r;
	ret_r = read(fd,gprs_buff,10);
	printf("%s\n",gprs_buff);
	return fd;

}*/
/**************************************************
 *函数名：rfid()
 *功  能：读卡，将卡号打印出来
 *参  数：fd
 *返回值：int型数组
**************************************************/
void rfid(int fd)
{
	memset(rbuff, '0', num);
	int ret;
	int i;
	ret = com_read(fd, rbuff, num);
	printf("%d",ret);
	printf("--------------");
	for(i = 0;i < ret;i++)
	{
		printf("%d",rbuff[i]);
	}
	printf("\n");
}
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
