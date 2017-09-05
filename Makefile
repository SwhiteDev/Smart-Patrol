CC = gcc
CFLAGS = -g 
LIB = -lsqlite3

SRC = main.c
SRC += ./serial/serial.c
SRC += ./rfid/rfid.c
SRC += ./gprs/socket.c
SRC += ./record_sql/record.c


OBJ = $(patsubst %c, %o, $(SRC))


all: Smart-Patrol


Smart-Patrol: $(OBJ) 
	$(CC) -o Smart-Patrol $(OBJ) $(LIB) $(CFLAGS)

$(OBJ): %.o: %.c


clean:
	-rm $(OBJ) Smart-Patrol -rf

