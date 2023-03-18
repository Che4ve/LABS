CC = gcc
CFLAGS = -std=c11 -Wall -Werror
FILE_NAME = queue
SOURCES = queue.c utils.c myqueue.c

all:
	$(CC) $(CFLAGS) $(SOURCES) 
	./a.out
clean:
	rm -f *.o
debug:
	$(CC) $(CFLAGS) -g $(SOURCES) 
comp:
	$(CC) $(CFLAGS) $(SOURCES) 
run:
	./a.out