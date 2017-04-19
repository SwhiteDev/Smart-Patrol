#include "mycom.h"
extern DWORD num;
extern const unsigned char *cmd[];
extern const unsigned char *post[];
extern BYTE gbuff[512];
extern BYTE rbuff[512];
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


	for(i = 7;i < 8;i++)
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
	for(j = 0;j < 5;j++)
	{
		memset(gbuff, '\0', num);
		w_ret = com_write(fd, post[j], strlen(post[j]));
		printf("GPRS写入命令：%s\n",post[j]);
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
