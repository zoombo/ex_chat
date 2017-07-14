CC=gcc
CFLAGS=-std=c11 -Wall -ggdb

all:main
	$(CC) $(CFLAGS) -lncurses -lpthread main.o -o ex_chat_server
main:
	$(CC) $(CFLAGS) -lncurses -lpthread -c main.c
#oth:
#	$(CC) $(CFLAGS) -lncurses -lpthread -c helpers.c
clean:
	rm ex_chat_server *.o


#gcc -std=c11 -Wall -lpthread -c async_copy.c
