#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <termios.h>
#include <time.h>
#include <sqlite3.h>
#include "record.h"

/************************************
 *函数名 : sql_create_table()
 *功能   : 创建数据库
 *参数   : sqlite3 *db
 *返回值 : void
 ***********************************/
void sql_create_table(sqlite3 *db)
{
	char *sql;
	char *zerr;

	sql = "CREATE TABLE Record(CardID VARCHAR(16) PRIMARY KEY,DeviceID VARCHAR(16),Time VARCHAR(16));";
	if(sqlite3_exec(db, sql, 0, 0, &zerr) != SQLITE_OK)
	{
		printf("create failed : %s\n", zerr);
	}
}

/**********************************************
 *函数名 : merg_sql()
 *功能   : 将设备号与卡号、时间合并到sql插入语句中
 *参数   : const unsigned char *device_id，设备ID
 		   unsigned char rbuff[]，卡号
 *返回值 : char *，合并后的sql语句字符串地址
 **********************************************/
char *merg_sql(const unsigned char *device_id, unsigned char rbuff[])
{
	static char after_insert_sql[100];
	time_t timep; 
	time(&timep);
	char *my_time;
	const char *tmp;    /*存储临时device_id*/

	/*将参数拼接到sql语句中*/
	strcpy(after_insert_sql, "INSERT INTO 'Record' VALUES(\'");
	strcat(after_insert_sql, rbuff);
	strcat(after_insert_sql, "\',\'");

	/*
	 *为了填充POST包方便，将device_id定义为"&device=device007"
	 *所以要截取出"device007"
	 */
	tmp = &device_id[8];

	strcat(after_insert_sql, tmp);
	strcat(after_insert_sql, "\'");
	strcat(after_insert_sql, ",\'");
	my_time = asctime(gmtime(&timep));
	strcat(after_insert_sql, my_time);
	
	/*删除时间字符串中的最后一个换行符*/
	{
		int length;
		char *p;

		length = strlen(after_insert_sql);
		p = after_insert_sql;
		after_insert_sql[length - 1] = '\0'; 
	}
	strcat(after_insert_sql, "\');");
	
	return after_insert_sql;
	//sql = "INSERT INTO 'Record' VALUSE(NULL, 101, 12:00);";
}

/*******************************************
 *函数名 : sql_insert()
 *功能   : 插入记录，即设备号，卡号，刷卡时间
 *参数   : 同merg_sql
 *返回值 : void
 *******************************************/
void sql_insert(sqlite3 *db, const unsigned char *device_id, unsigned char rbuff[])
{
	char *sql;
	char *zerr;

	sql = merg_sql(device_id, rbuff);
	printf("%s\n", sql);
	if(sqlite3_exec(db, sql, 0, 0, &zerr) != SQLITE_OK);
	{
		printf("insert failed : %s\n", zerr);
	}
}
