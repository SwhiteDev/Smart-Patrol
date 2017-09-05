CC = gcc
CFLAGS = -g 

SRC += socket.c

OBJ = $(patsubst %c, %o, $(SRC))

socket : $(OBJ) 
	$(CC) -o socket $(OBJ) $(CFLAGS)

$(OBJ): %.o: %.c


clean:
	-rm $(OBJ) socket -rf

