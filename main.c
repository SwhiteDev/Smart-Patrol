#include "com.h"
DWORD num = 512;
unsigned short rfid_buff[512];
char gprs_buff[512];

int main()
{
	int rfid_fd = -1;
	rfid_fd = rfid_init();
	rfid(rfid_fd);
//	int gprs_fd = gprs_init();
	return 0;
}

/**************************************************
 *函数名：gprs_init()
 *功  能：初始化gprs模块接口，与服务器建立tcp链接
 *参  数：void
 *返回值：int
**************************************************/
int gprs_init(void)
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

}
/**************************************************
 *函数名：rfid()
 *功  能：读卡，将卡号打印出来
 *参  数：fd
 *返回值：int型数组
**************************************************/
void rfid(int fd)
{
	memset(rfid_buff,'0',num);
	int ret;
	int i;
	while((ret = read(fd,rfid_buff,num)) >= 0)
	{
		if(ret > 5)
		{
		printf("%d---------------",ret);
		for(i = 0;i < 5;i++)
		{
		printf("%d-",rfid_buff[i]);
		}
		printf("\n");
		}
//		else
//		printf("waiting!");
//		sleep(5);
	}
}
/**************************************************
 *函数名：rfid_init()
 *功  能：初始化rfid模块接口
 *参  数：void
 *返回值：int
**************************************************/
int rfid_init(void)
{
	DEV_COM_RFID = "/dev/ttyUSB0";
	int fd = CommOpen(DEV_COM_RFID);
	COMM_ATTR attr = {0};
	attr.baudrate = 19200;
	attr.databits = 8;
	attr.parity = COMM_NOPARITY;
	attr.stopbits = COMM_ONESTOPBIT;
	if(SetAttribute(fd,&attr) != 0)
		printf("set com_rfid attr failed\n");
	GetAttribute(fd);
	return fd;
}
int CommOpen(char *DEV)
{	
	int fd = -1;
	fd = open(DEV, O_RDWR|O_NOCTTY|O_NDELAY);
	fcntl(fd,F_SETFL,0);
	if (fd < 0)
	{
		ERR_PRINT("open com dev\n");
		return -1;
	}
	LIBDVR_PRINT("CommOpen Successful\n");
	return fd;
}

/**************************************************
 *函数名：CommDestory()
 *功  能：关闭串口
 *参  数：fd
 *返回值：int
**************************************************/
int CommDestory(int fd)
{
	int ret = -1;

	if(fd > 0)
	{
		printf("close start!\n");
		ret = close(fd);
		printf("close end!\n");
		fd = -1;		
	}

	return ret;
}
/**************************************************
 *函数名：SetAttribute()
 *功  能：设置串口参数
 *参  数：int fd,参数结构体COMM_ATTR *pattr
 *返回值：int fd
**************************************************/
int SetAttribute(int fd,COMM_ATTR *pattr)
{
	int dev_fd = fd;
	struct termios opt;
	COMM_ATTR *attr = pattr;
	
	if (dev_fd < 0)
	{
		return -1;
	}

	memset(&opt, 0, sizeof(struct termios));
	tcgetattr(dev_fd, &opt);
	cfmakeraw(&opt);			

	
	printf("set baudrate %d\n", attr->baudrate);
	switch (attr->baudrate)
	{
		case 50:
			cfsetispeed(&opt, B50);
			cfsetospeed(&opt, B50);
			break;
		case 75:
			cfsetispeed(&opt, B75);
			cfsetospeed(&opt, B75);
			break;
		case 110:
			cfsetispeed(&opt, B110);
			cfsetospeed(&opt, B110);
			break;
		case 134:
			cfsetispeed(&opt, B134);
			cfsetospeed(&opt, B134);
			break;
		case 150:
			cfsetispeed(&opt, B150);
			cfsetospeed(&opt, B150);
			break;
		case 200:
			cfsetispeed(&opt, B200);
			cfsetospeed(&opt, B200);
			break;
		case 300:
			cfsetispeed(&opt, B300);
			cfsetospeed(&opt, B300);
			break;
		case 600:
			cfsetispeed(&opt, B600);
			cfsetospeed(&opt, B600);
			break;
		case 1200:
			cfsetispeed(&opt, B1200);
			cfsetospeed(&opt, B1200);
			break;
		case 1800:
			cfsetispeed(&opt, B1800);
			cfsetospeed(&opt, B1800);
			break;
		case 2400:
			cfsetispeed(&opt, B2400);
			cfsetospeed(&opt, B2400);
			break;
		case 4800:
			cfsetispeed(&opt, B4800);
			cfsetospeed(&opt, B4800);
			break;
		case 9600:
			cfsetispeed(&opt, B9600);
			cfsetospeed(&opt, B9600);
			break;
		case 19200:
			cfsetispeed(&opt, B19200);
			cfsetospeed(&opt, B19200);
			break;
		case 38400:
			cfsetispeed(&opt, B38400);
			cfsetospeed(&opt, B38400);
			break;
		case 57600:
			cfsetispeed(&opt, B57600);
			cfsetospeed(&opt, B57600);
			break;
		case 115200:
			cfsetispeed(&opt, B115200);
			cfsetospeed(&opt, B115200);
			break;
		case 230400:
			cfsetispeed(&opt, B230400);
			cfsetospeed(&opt, B230400);
			break;
		case 460800:
			cfsetispeed(&opt, B460800);
			cfsetospeed(&opt, B460800);
			break;
		case 500000:
			cfsetispeed(&opt, B500000);
			cfsetospeed(&opt, B500000);
			break;
		case 576000:
			cfsetispeed(&opt, B576000);
			cfsetospeed(&opt, B576000);
			break;
		case 921600:
			cfsetispeed(&opt, B921600);
			cfsetospeed(&opt, B921600);
			break;
		case 1000000:
			cfsetispeed(&opt, B1000000);
			cfsetospeed(&opt, B1000000);
			break;
		case 1152000:
			cfsetispeed(&opt, B1152000);
			cfsetospeed(&opt, B1152000);
			break;
		case 1500000:
			cfsetispeed(&opt, B1500000);
			cfsetospeed(&opt, B1500000);
			break;
		case 2000000:
			cfsetispeed(&opt, B2000000);
			cfsetospeed(&opt, B2000000);
			break;
		case 2500000:
			cfsetispeed(&opt, B2500000);
			cfsetospeed(&opt, B2500000);
			break;
		case 3000000:
			cfsetispeed(&opt, B3000000);
			cfsetospeed(&opt, B3000000);
			break;
		case 3500000:
			cfsetispeed(&opt, B3500000);
			cfsetospeed(&opt, B3500000);
			break;
		case 4000000:
			cfsetispeed(&opt, B4000000);
			cfsetospeed(&opt, B4000000);
			break;
		default:
			LIBDVR_PRINT("unsupported baudrate %d\n", attr->baudrate);
			break;
	}

	
	switch (attr->parity)
	{
		case COMM_NOPARITY:		
			opt.c_cflag &= ~PARENB;	
			opt.c_iflag &= ~INPCK;	
			break;
		case COMM_ODDPARITY:		
			opt.c_cflag |= PARENB;	
			opt.c_cflag |= PARODD;	
			opt.c_iflag |= INPCK;	
			break;
		case COMM_EVENPARITY:		
			opt.c_cflag |= PARENB;	
			opt.c_cflag &= ~PARODD;	
			opt.c_iflag |= INPCK;	
		default:
			LIBDVR_PRINT("unsupported parity %d\n", attr->parity);
			break;
	}

	
	opt.c_cflag &= ~CSIZE;
	switch (attr->databits)
	{
		case 5:
			opt.c_cflag |= CS5;
			break;
		case 6:
			opt.c_cflag |= CS6;
			break;
		case 7:
			opt.c_cflag |= CS7;
			break;
		case 8:
			opt.c_cflag |= CS8;
			break;
		default:
			LIBDVR_PRINT("unsupported data bits %d\n", attr->databits);
			break;
	}

	
	opt.c_cflag &= ~CSTOPB;
	switch (attr->stopbits)
	{
		case COMM_ONESTOPBIT:
			opt.c_cflag &= ~CSTOPB;
			break;

		case COMM_TWOSTOPBITS:
			opt.c_cflag |= CSTOPB;
			break;
		default:
			LIBDVR_PRINT("unsupported stop bits %d\n", attr->stopbits);
			break;
	}
	opt.c_cc[VTIME]	= 0;
	opt.c_cc[VMIN]	= 1;			

	tcflush(dev_fd, TCIOFLUSH);
	if (tcsetattr(dev_fd, TCSANOW, &opt) < 0)
	{
		ERR_PRINT("tcsetattr\n");
		return -1;
	}

	return 0;
} 
/**************************************************
 *函数名：GetAttribute()
 *功  能：完成设置串口参数
 *参  数：int fd
 *返回值：int fd
**************************************************/
int GetAttribute(int fd)
{
	int dev_fd = fd;
	struct termios opt;

	if (dev_fd < 0)
	{
		return -1;
	}

	memset(&opt, 0, sizeof(struct termios));
	tcgetattr(dev_fd, &opt);
	cfmakeraw(&opt);			
	return 0;
} 
/**************************************************
 *函数名：CommRead()
 *功  能：读串口
 *参  数：int fd,char *pdata,DWORD nbytes
 *返回值：int 读取字节数
**************************************************/
int CommRead(int fd,char *pdata, DWORD nbytes)
{	
	if (fd < 0)
	{
		ERR_PRINT("Can't Open Com Dev");
		return -1;
	}
	printf("start to read!\n");
	return read(fd, pdata, nbytes);
}
/**************************************************
 *函数名：CommWrite()
 *功  能：写串口
 *参  数：int fd,char *pdata,DWORD len
 *返回值：int 写入字节数
**************************************************/
int CommWrite(int fd,char *pdata, DWORD len)
{	
	if (fd < 0)
	{
		ERR_PRINT("Can't Open Com Dev");
		return -1;
	}		
	
	printf("start to write!\n");
	return write(fd, pdata, len);
}


int CommPurge(int fd,DWORD dw_flags)
{
	if (fd < 0)
	{
		ERR_PRINT("Can't Open Com Dev");
		return -1;
	}		
	switch (dw_flags)
	{
		case COMM_PURGE_TXABORT:
			tcflow(fd, TCOOFF);
			break;
		case COMM_PURGE_RXABORT:
			tcflow(fd, TCIOFF);
			break;
		case COMM_PURGE_TXCLEAR:
			tcflush(fd, TCOFLUSH);
			break;
		case COMM_PURGE_RXCLEAR:
			tcflush(fd, TCIFLUSH);
			break;
		default:
			LIBDVR_PRINT("Unknow flag\n");
			return -1;
	}

	return 0;
}
