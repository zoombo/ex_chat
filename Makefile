CC=gcc
CFLAGS=-std=c11 -Wall -ggdb

all:main oth
	$(CC) $(CFLAGS) -lncurses -lpthread main.o helpers.o -o ex_chat
main:
	$(CC) $(CFLAGS) -lncurses -lpthread -c main.c
oth:
	$(CC) $(CFLAGS) -lncurses -lpthread -c helpers.c
clean:
	rm ex_chat *.o


#gcc -std=c11 -Wall -lpthread -c async_copy.c
