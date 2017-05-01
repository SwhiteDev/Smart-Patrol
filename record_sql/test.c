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

int main()
{
	const unsigned char *device_id = "00000007";
    unsigned char rbuff[] = "122345678";
	sqlite3 *db;
	int ret = sqlite3_open("record.db",&db);
	if(ret)
	{
		fprintf(stderr, "can't open database: %s\n", sqlite3_errmsg(db));
		return 0;
	}

	//sql_create_table(db);
	sql_insert(db, device_id, rbuff);
}
