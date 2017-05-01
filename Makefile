CC = gcc -g -o
LIB = -lsqlite3
SRC = main.c ./com/mycom.c ./init/init.c ./record_sql/record.c

#all : Smart-Patrol record

Smart-Patrol : $(SRC)
	$(CC) Smart-Patrol $(SRC) $(LIB)

#record : record.c
#	$(CC) record record.c $(LIB)
