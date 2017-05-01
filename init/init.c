#include "mycom.h"

unsigned char rbuff[512];   /*rfid读取缓冲区*/
unsigned char gbuff[512];   /*gprs读取缓冲区*/
unsigned short num = 512;   /*读取和写入字节*/


/****命令缓冲区，cmd为初始化AT指令，post为post数据包****/
unsigned char *cmd[] = {
						"AT\r", 				 \
						"AT+CCID\r", 				\
						"AT+CSQ\r", 				\
						"AT+CGCLASS=\"B\"\r", 				\
						"AT+CGDCONT=1,\"IP\",\"CMNET\"\r", 				\
						"AT+CGATT=1\r", 				\
						"AT+CIPCSGP=1,\"CMNET\"\r", 				\
						"AT+CIPSTART=\"TCP\",\"182.254.244.212\",\"80\"\r", 				\
						"AT+CIPSEND\r", 				\
						"AT+CIPCLOSE\r" 				\
	 				   };

unsigned char *post[] = {
				   		 "POST /xg/index.php/admin/upload/record HTTP/1.1\r\n", 				\
			   	  		 "Host: www.hicoder.cn\r\n", 				\
			       		 "Content-Type: application/x-www-form-urlencoded\r\n", 				\
			   	    	 "Content-Length: 42\r\n\r\n", 				\
				   		 "key=iot&location=002&device=device001"  				\
			   			};


/**************************************************
 *函数名：rfid_init()
 *功  能：初始化rfid模块接口
 *参  数：void
 *返回值：int fd
**************************************************/
int rfid_init(void)
{
	const char *dev = "/dev/ttyUSB0";
	int fd = com_open(dev);

	/*设置波特率乱七八糟的*/
	com_attr attr = {0};
	attr.baudrate = 19200;
	attr.databits = 8;
	attr.parity = COMM_NOPARITY;
	attr.stopbits = COMM_ONESTOPBIT;
	if(set_com_attr(fd, &attr) != 0)
		printf("set com_rfid attr failed\n");
	get_com_attr(fd);
	return fd;
}


/**************************************************
 *函数名：gprs_init()
 *功  能：初始化gprs模块接口，与服务器建立tcp链接
 *参  数：void
 *返回值：int fd
**************************************************/
int gprs_init()
{
	int r_ret, w_ret, i;
	char *dev = "/dev/ttyUSB1";
	int fd = com_open(dev);
	
	/*设置波特率乱七八糟的*/
	com_attr attr = {0};
	attr.baudrate = 9600;
	attr.databits = 8;
	attr.parity = COMM_NOPARITY;
	attr.stopbits = COMM_ONESTOPBIT;
	if(set_com_attr(fd, &attr) != 0)
		printf("set com_gprs attr failed\n");
	get_com_attr(fd);


	/**建立链接**/
	for(i = 0;i < 7;i++)
	{
		memset(gbuff, '\0', num);
		w_ret = com_write(fd, cmd[i], strlen(cmd[i]));
		printf("GPRS写入命令：%s\n",cmd[i]);
		printf("GPRS写入字节数：%d\n",w_ret);

		sleep(1);


		r_ret = com_read(fd, gbuff, num);
		printf("GPRS返回命令：%s\n", gbuff);
		printf("GPRS返回字节数：%d\n", r_ret);
		sleep(1);
	}
	return fd;
}
