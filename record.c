#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include <sqlite3.h>

#define TRUE 1
#define FALSE 0

int sql_create_table(sqlite3 *db)
{
	char *sql;
	char *zerr;

	sql = "CREATE TABLE Record(ID INTEGER PRIMARY KEY,DeviceID,Time VARCHAR(12));";
	if(sqlite3_exec(db, sql, 0, 0, &zerr) != SQLITE_OK)
	{
		printf("create failed : %s\n", zerr);
		return FALSE;
	}
}

char *insert_sql(const unsigned char *device_id, unsigned char rbuff[])
{
	static char after_insert_sql[100];
	time_t timep;
	time(&timep);
	char *my_time;

	strcpy(after_insert_sql, "INSERT INTO 'Record' VALUSE(");
	strcat(after_insert_sql, rbuff);
	strcat(after_insert_sql, ",");
	strcat(after_insert_sql, device_id);
	strcat(after_insert_sql, ",");
	my_time = asctime(gmtime(&timep));
	strcat(after_insert_sql, my_time);
	strcat(after_insert_sql)
	
	return after_insert_sql;
	//sql = "INSERT INTO 'Record' VALUSE(NULL, 101, 12:00);";
}

int main()
{
	const unsigned char *device_id = "007";
	unsigned char rbuff[] = "123456";
	char *ret = insert_sql(device_id, rbuff);
	printf("%s\n", ret);
}
