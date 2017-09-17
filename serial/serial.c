#include "serial.h"

/*
 * 以非阻塞方式打开串口（为什么不用阻塞方式）
 */
int serial_open(const char *DEV)
{
	int fd = -1;
	if(-1 == (fd = open(DEV, O_RDWR | O_NOCTTY | O_NDELAY))){
		perror("open serial error");
		return -1;
	}
	/*fcntcl(fd, F_SETFL, 0);  阻塞*/
	return fd;
}

/*
 * 设置串口属性
 */
int set_serial_attr(int fd, serial_attr *attr)
{
	struct termios opt;
	if(fd < 0 || NULL == attr){
		printf("bad param\n");
		return -1;
	}
	memset(&opt, 0, sizeof(struct termios));
	tcgetattr(fd, &opt);
	cfmakeraw(&opt);


	/***********baudrate************/
	printf("set baudrate %d\n", attr->baudrate);
	switch(attr->baudrate){
		case 9600:
			cfsetispeed(&opt, B9600);
			cfsetospeed(&opt, B9600);
			break;
		case 19200:
			cfsetispeed(&opt, B19200);
			cfsetospeed(&opt, B19200);
			break;
		case 115200:
			cfsetispeed(&opt, B115200);
			cfsetospeed(&opt, B115200);
		default:
			printf("unsurported baudrate %d\n", attr->baudrate);
			return -1;
			break;
	}


	/************parity*************/
	switch(attr->parity){
		case BITS_PARITY_NONE:
			opt.c_cflag &= ~PARENB;
			opt.c_iflag &= ~INPCK;
			break;
		case BITS_PARITY_ODD:
			opt.c_cflag |= (PARENB | PARODD);
			opt.c_iflag |= INPCK;
			break;
		case BITS_PARITY_EVEN:
			opt.c_cflag |= PARENB;
			opt.c_cflag &= ~PARODD;
			opt.c_iflag |= INPCK;
			break;
		default:
			printf("unsurported parity %d\n", attr->parity);
			return -1;
			break;
	}
		opt.c_cflag &= ~CSIZE;


	/***********databits*************/
	switch(attr->databits){
		case BITS_DATA_5:
			opt.c_cflag |= CS5;
			break;
		case BITS_DATA_6:
			opt.c_cflag |= CS6;
			break;
		case BITS_DATA_7:
			opt.c_cflag |= CS7;
			break;
		case BITS_DATA_8:
			opt.c_cflag |= CS8;
			break;
		default:
			printf("unsurported databits %d\n", attr->databits);
			return -1;
			break;
	}


	/***********stopbits************/
	switch(attr->stopbits){
		case BITS_STOP_1:
			opt.c_cflag &= ~CSTOP;
			break;
		case BITS_STOP_2:
			opt.c_cflag |=  CSTOP;
			break;
		default:
			printf("unsurported stopbits %d\n", attr->stopbits);
			return -1;
			break;
	}


	/*wait time*/
	opt.c_cc[VTIME] = 0;
	opt.c_cc[VMIN]  =1;


	opt.c_iflag &= ~(ICRNL | INLCR);
	opt.c_iflag &= ~(IXON | IXOFF | IXANY);

	tcflush(fd, TCIOFLUSH);
	if(tcsetattr(fd, TCSANOW, &opt) < 0){
		perror("tcsetattr faild\n");
		return -1;
	}
	return 0;
}


/*
 * 读串口
 */
int serial_read(int fd, char *rbuff, unsigned int nbytes)
{
	if(fd < 0){
		printf("fd error :fd = %d\n", fd);
		return -1;
	}
	if(NULL == rbuff){
		printf("read_buff error\n");
		return -1;
	}
	if(0 == nbytes){
		printf("read size error\n");
		return -1;
	}
	return read(fd, rbuff, nbytes);
}


/*
 * 写串口
 */
int serial_write(int fd, char *wbuff, unsigned int nbytes)
{
	if(fd < 0){
		printf("fd error :fd = %d\n", fd);
		return -1;
	}
	if(NULL == wbuff){
		printf("read_buff error\n");
		return -1;
	}
	if(0 == nbytes){
		printf("write size error\n");
		return -1;
	}
	return write(fd, wbuff, nbytes);
}


/*
 * 关闭串口
 */
int serial_close(int fd)
{
	if(fd < 0){
		printf("fd error :fd = %d\n", fd);
		return -1;
	}
	return close(fd);
}


/*
 * 刷新缓冲IO(此处查一下tcflush函数用法)
 */
int serial_flushio(int fd)
{
	return tcflush(fd, TCIOFLUSH);
}
