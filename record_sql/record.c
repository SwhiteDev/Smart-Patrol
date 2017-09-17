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

#define NO_SUCH_TABLE "no such table"

static int count = 0;
static int callback(void *data, int argc, char **argv, char **azColName)
{
   ++count;
   return 0;
}

static is_table_exist(sqlite3 *db, char *table_name)
{
	char sql[256] = {0};
	char *zerr;
	sprintf(sql, "SELECT count(*) FROM %s;", table_name);
	if(sqlite3_exec(db, sql, callback, NULL, &zerr) != 0){
		fprintf(stderr, "count table error:%s\n", zerr);
		if(strncmp(NO_SUCH_TABLE, zerr, strlen(NO_SUCH_TABLE)) == 0){
			return 0;
		}
		return -1;
	}
	return count != 0;
}
/************************************
 
 ***********************************/

int  sql_create_table(sqlite3 *db, char *table_name)
{
	char sql[256] = {0};
	char *zerr;
	if (!is_table_exist(db, table_name)){
	
		sprintf(sql, "CREATE TABLE %s(card_id VARCHAR(16) , device_id VARCHAR(16), time VARCHAR(32));", table_name);
		if(sqlite3_exec(db, sql, NULL, NULL, &zerr) != SQLITE_OK)
		{
			printf("create failed : %s\n", zerr);
			return -1;
		}
	}
	return 0;
}

/*
 * 数据库插入操作 
 */
int sql_insert(sqlite3 *db,char *table_name,unsigned char *card_id, char *device_id)
{
	static char sql[128];
	time_t timep; 
	char *zerr;
	char *time_str = NULL;
	char *tmp_sql = "INSERT INTO '%s' (card_id, device_id, time) VALUES ('%s', '%s', '%s');"; 
	char tmp_time[32] = {0};
	
	
	time(&timep);
	time_str = asctime(gmtime(&timep));
	memset(tmp_time, 0x00, 32);
	strncpy(tmp_time, time_str, strlen(time_str)-1);
	sprintf(sql, tmp_sql, table_name, card_id, device_id, tmp_time);

	printf("sql:%s\n", sql);
	sqlite3_exec(db, sql, 0, 0, &zerr);	
	
	return 0;
}
