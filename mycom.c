#include "mycom.h"

BYTE rbuff[512];
BYTE gbuff[512];

int com_open(const char *dev)
{
	int fd = -1;
	fd = open(dev, O_RDWR | O_NOCTTY | O_NDELAY);
	if(fd == -1)
	{
		printf("串口打开失败!");
		exit(0);
	}
//	fcntl(fd, F_SETFL, 0);    /*设置以阻塞模式打开*/
	return fd;
}


/**************************************************
 *函数名：set_com_attr()
 *功  能：设置串口属性
 *参  数：int fd,属性结构体com_arrt *attr
 *返回值：void
**************************************************/
int set_com_attr(int fd, com_attr *attr)
{
	struct termios opt;
//	com_attr *attr = pattr;
	memset(&opt, 0, sizeof(struct termios));
	tcgetattr(fd, &opt);
	cfmakeraw(&opt);    
	
	
	/*******************波特率********************/
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
			printf("unsupported baudrate %d\n", attr->baudrate);
			return FALSE;
			break;
	}

	/************************校验位************************/
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
			printf("unsupported parity %d\n", attr->parity);
			return FALSE;
			break;
	}
			opt.c_cflag &= ~CSIZE;       /*无论设置多少校验位都需要的*/
	

        /*******************数据位*****************/
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
			printf("unsupported data bits %d\n", attr->databits);
			return FALSE;
			break;
	}
	opt.c_cflag &= ~CSTOPB;

	/*******************停止位***************/
	switch (attr->stopbits)       
	{
		case COMM_ONESTOPBIT:
			opt.c_cflag &= ~CSTOPB;
			break;

		case COMM_TWOSTOPBITS:
			opt.c_cflag |= CSTOPB;
			break;
		default:
			printf("unsupported stop bits %d\n", attr->stopbits);
			return FALSE;
			break;
	}
	
	/*等待时间*/
	opt.c_cc[VTIME]	= 0;
	opt.c_cc[VMIN]	= 1;	
	
	/*非阻塞*/
	opt.c_iflag &= ~(ICRNL | INLCR);
	opt.c_iflag &= ~(IXON | IXOFF | IXANY);
	
	tcflush(fd, TCIOFLUSH);	       //刷清缓冲区
	if (tcsetattr(fd, TCSANOW, &opt) < 0)
	{
		printf("tcsetattr faild\n");
		return FALSE;
	}
	return TRUE;
}


/**************************************************
 *函数名：get_com_attr()
 *功  能：获取串口属性
 *参  数：int fd
 *返回值：void
**************************************************/
void get_com_attr(int fd)
{
	struct termios opt;
	if(fd < 0)
	{
		printf("get_com_attr error");
		exit(0);
	}
	memset(&opt, 0, sizeof(struct termios));
	tcgetattr(fd, &opt);
	cfmakeraw(&opt);
} 

/**************************************************
 *函数名：com_read()
 *功  能：读串口操作
 *参  数：int fd，unsigned char *rbuff, unsigned int nbytes
 *返回值：int ret读取字节数
**************************************************/
int com_read(int fd, BYTE *rbuff, DWORD nbytes)
{
	int ret;
	if(fd < 0)
	{
		printf("com_read error");
		exit(0);
	}
	ret = read(fd, rbuff, nbytes);
	return ret;
}

/**************************************************
 *函数名：com_write()
 *功  能：写串口操作
 *参  数：int fd，unsigned char *wbuff, unsigned int nbytes
 *返回值：int ret写入字节数
**************************************************/
int com_write(int fd, BYTE *wbuff, DWORD nbytes)
{
	int ret;
	if(fd < 0)
	{
		printf("com_write error");
		exit(0);
	}
	ret = write(fd, wbuff, nbytes);
	return ret;
}

/**************************************************
 *函数名：com_close()
 *功  能：关闭串口
 *参  数：fd
 *返回值：void
**************************************************/
void com_close(int fd)
{
	if(fd < 0)
	{
		printf("com_close error");
		exit(0);
	}
	close(fd);
}

