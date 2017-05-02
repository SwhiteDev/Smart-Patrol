#include "./com/mycom.h"
#include "./record_sql/record.h"

extern DWORD num;
extern unsigned char *cmd[];    //AT命令
extern unsigned char *post[];    //post数据包
extern BYTE gbuff[512];
extern BYTE rbuff[512];
const unsigned char *device_id = "&device=device007";     //每个终端(树莓派)固定的设备号

/*******************************************
 *主函数 : main()
 *参数   : void
 *返回值 : int
 *功能   : 初始化RFID、GPRS模块、创建数据库;
		   循环读取rfid卡号;
		   读到卡号时调用gprs()
 *******************************************/
int main(void)
{
	int rfid_fd = -1;
	int gprs_fd = -1;
	int flag = 0;
	sqlite3 *db;

	int ret = sqlite3_open("./record_sql/record.db",&db);
	if(ret)
	{
		fprintf(stderr, "can't open database: %s\n", sqlite3_errmsg(db));
	}

	/*初始化RFID、GPRS*/
	rfid_fd = rfid_init();
	gprs_fd = gprs_init();

	/*建表，第二次运行程序就可以把这行注释了。。。。。。。。。。*/
	sql_create_table(db);


	/*循环读卡*/
	while(1)
	{
		flag = rfid(rfid_fd, db);
		if(flag > 0)
		{
			printf("\n\n等待GPRS执行模块......\n\n");
			gprs(gprs_fd);
			printf("本次签到完成！！！\n\n");
		}
	}
	return 0;
}

/*************************************************
 *函数名 : gprs()
 *参数   : int fd
 *返回值 : void
 *功能   : 发送初始化指令(为了节省流量每次执行后都
 		   关闭TCP链接),建立TCP链接，发送POST数据包
 *************************************************/
void gprs(int fd)
{
	int w_ret,r_ret;
	int i,j;
	char over_flag = 0x1a;

	for(i = 7;i < 9;i++)
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
	com_write(fd, &over_flag, sizeof(over_flag));   //发送0X1A结束指令
	

	sleep(2);
	printf("发送中POST数据包中......\n\n");
	r_ret = com_read(fd, gbuff, num);
	printf("服务器返回数据：%s\n",gbuff);
	printf("返回字节数：%d\n",r_ret);
	

	/*关闭TCP链接*/
	memset(gbuff, '\0', num);
	com_write(fd, cmd[9], strlen(cmd[9]));
	sleep(2);
	r_ret = com_read(fd, gbuff, num);
	printf("关闭：%s\n",gbuff);
}


/**********************************************
 *函数名 : rfid()
 *功  能 : 读卡，将卡号打印出来;
 		   将刷卡时间、设备、卡号存入数据库
 *参  数 : int fd
 *返回值 : int型,卡号位数(用于辨别是否有读到卡)
 **********************************************/
int rfid(int fd, sqlite3 *db)
{
	int ret;
	int i,j;
	char tmp;


	memset(rbuff, '\0', num);
	sleep(1);
	ret = com_read(fd, rbuff, num);
	printf("RFID接收字节数：%d\n",ret);
	printf("卡号：");


	/*将卡号转换为字符串*/
	for(j = 0;j < ret;j++)
	{
		tmp = (((int)rbuff[j])%3) + (48 + j%2);
		rbuff[j] = tmp;
	}


	/*打印卡号,并将卡号填充到POST数据包*/
	if(ret > 0)
	{
		/*调用数据库函数*/
		sql_insert(db, device_id, rbuff);
		printf("%s\n",rbuff);
		card_to_post(rbuff);
	}
	else
	{
		printf("********请刷卡********");
	}
	printf("\n");
	return ret;
}


/***********************************************
 *函数名 : card_to_post()
 *功能   : 将卡号填充到POST数据包
 *参数   : unsigned char card[]，卡号字符串数组地址
 *返回值 : void
 **********************************************/
void card_to_post(unsigned char card[])
{
	/*.................各种拼接*/
	unsigned char part_1[50] = "key=iot&location=";
	unsigned char part_2[50];
	strcpy(part_2, card);
	unsigned char part_3[100];
	strcpy(part_3, device_id);
	unsigned char part_1_2[100];
	strcpy(part_1_2, strcat(part_1, part_2));
	static unsigned char part_1_2_3[100];
	memset(part_1_2_3, '\0', 100);
	strcpy(part_1_2_3, strcat(part_1_2, part_3));


	/*将最终拼接结果字符串地址赋给post[4]*/
	post[4] = part_1_2_3;
}
