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

	
build-tests:
	$(CC) $(CFLAGS) -lncurses -lpthread ./Tests/chatter_test.c chatter2.c -o chatter_test
test:
	./chatter_test
	
#gcc -std=c11 -Wall -lpthread -c async_copy.c
