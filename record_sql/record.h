#ifndef RECORD_H
#define RECORD_H

#include <sqlite3.h>
int  sql_insert(sqlite3 *db,char *table_name,unsigned char *card_id, char *device_id);
int  sql_create_table(sqlite3 *db, char *table_name);


#endif