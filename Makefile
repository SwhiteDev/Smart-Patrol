cc = gcc -o
src = main.c mycom.c init.c

all : Smart-Patrol record

Smart-Patrol : $(src)
	$(cc) Smart-Patrol $(src)

record : record.c
	$(cc) record record.c -lsqlite3
