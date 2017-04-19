#include "mycom.h"

const  BYTE device_id;    /*每个设备固定的设备号*/
extern BYTE rbuff[512];   /*rfid读取缓冲区*/
extern BYTE gbuff[512];   /*gprs读取缓冲区*/
DWORD num = 512;          /*读取和写入字节*/

/****命令缓冲区，cmd为初始化AT指令，post为post数据包****/
const unsigned char *cmd[] = {
								"AT\r", 				 \
								"AT+CCID\r", 				\
								"AT+CSQ\r", 				\
								"AT+CGCLASS=\"B\"\r", 				\
								"AT+CGDCONT=1,\"IP\",\"CMNET\"\r", 				\
								"AT+CGATT=1\r", 				\
								"AT+CIPCSGP=1,\"CMNET\"\r", 				\
								"AT+CIPSTART=\"TCP\",\"182.254.244.212\",\"80\"\r", 				\
								"AT+CIPSEND=181\r", 				\
								"AT+CIPCLOSE\r" 				\
					   		 };

const unsigned char *post[] = {
							   "POST /xg/index.php/admin/upload/record\r\n", 				\
							   "Host: www.hicoder.cn\r\n", 				\
						       "Content-Type:application/x-www-form-urlencoded\r\n", 				\
						   	   "Content-Length:37\r\n\r\n", 				\
							   "key=iot&location=002&device=device001"  				\
							  };
/**************************************************
主函数 : main()
参数   : void
返回值 : int
功能   : 初始化rfid和gprs模块的接口  \
		 循环读取rfid卡号，缓冲区有数据时调用gprs()
***************************************************/
int main(void)
{
	int rfid_fd = -1;
	int gprs_fd = -1;
	int flag = 0;
	rfid_fd = rfid_init();
	gprs_fd = gprs_init();

	/*循环读卡*/
	while(1)
	{
		flag = rfid(rfid_fd);
		if(flag > 0)
		{
			printf("\n\n等待GPRS执行模块......\n\n");
			gprs(gprs_fd);
			printf("本次签到完成！！！");
		}
	}
	return 0;
}


/*************************************************
函数名 : gprs()
参数   : int fd
返回值 : void
功能   : 发送初始化指令(为了节省流量每次执行后都关
		 闭TCP链接),建立TCP链接，发送POST数据包
*************************************************/
void gprs(int fd)
{
	int w_ret,r_ret;
	int i,j;

	/**建立链接**/
	for(i = 0;i < 9;i++)
	{
		memset(gbuff, '\0', num);
		w_ret = com_write(fd, cmd[i], strlen(cmd[i]));
		printf("GPRS写入命令：%s\n",cmd[i]);
		printf("GPRS写入字节数：%d\n",w_ret);

		sleep(1);


		r_ret = com_read(fd, gbuff, num);
		printf("GPRS返回命令：%s\n",gbuff);
		printf("GPRS返回字节数：%d\n",r_ret);
		sleep(1);
	}


	/*当执行到SEND命令时开始发送POST数据包*/
	memset(gbuff, '\0', num);
	for(j = 0;j < 5;j++)
	{
		w_ret = com_write(fd, post[j], strlen(post[j]));
		printf("GPRS写入命令：%s\n",post[i]);
		printf("GPRS写入字节数：%d\n",w_ret);
	}
	sleep(1);
	printf("发送成功！");
	r_ret = com_read(fd, gbuff, num);
	printf("服务器返回数据：%s\n",gbuff);
	printf("返回字节数：%d\n",r_ret);
	

	/*关闭TCP链接*/
	memset(gbuff, '\0', num);
	com_write(fd, cmd[9], strlen(cmd[9]));
	r_ret = com_read(fd, gbuff, num);
	printf("%s\n",gbuff);
}


/**************************************************
 *函数名：rfid()
 *功  能：读卡，将卡号打印出来
 *参  数：fd
 *返回值：int型数组
**************************************************/
int rfid(int fd)
{
	memset(rbuff, '0', num);
	int ret;
	int i;

	sleep(2);
	ret = com_read(fd, rbuff, num);
	printf("RFID接收字节数：%d\n",ret);
	printf("卡号：");
	for(i = 0;i < ret;i++)
	{
		printf("%d",rbuff[i]);
	}
	printf("\n");
	return ret;
}
