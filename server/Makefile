CC=gcc
CFLAGS=-std=c11 -Wall -ggdb

all:main oth
	$(CC) $(CFLAGS) -lncurses -lpthread main.o queue.o chatter2.o -o ex_chat_server
main:
	$(CC) $(CFLAGS) -lncurses -lpthread -c main.c
oth:
	$(CC) $(CFLAGS) -lncurses -lpthread -c queue.c chatter2.c
clean:
	rm ex_chat_server *.o


#gcc -std=c11 -Wall -lpthread -c async_copy.c
