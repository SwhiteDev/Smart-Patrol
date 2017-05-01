void sql_insert(sqlite3 *db, const unsigned char *device_id, unsigned char rbuff[]);
char *merg_sql(const unsigned char *device_id, unsigned char rbuff[]);
void sql_create_table(sqlite3 *db);
