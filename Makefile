CC = gcc
DEGUGGER = gdb
CFLAGS = -std=c11 -Wall -Werror
FILE_OUT = queue.out
SOURCES = queue.c myqueue.c

all:
	$(CC) $(CFLAGS) $(SOURCES) -o $(FILE_OUT)
	./$(FILE_OUT)
clean:
	rm -f *.o
debug:
	$(CC) $(CFLAGS) -g $(SOURCES) 
	sudo $(DEGUGGER) $(FILE_OUT)
comp:
	$(CC) $(CFLAGS) $(SOURCES) -o $(FILE_OUT)
run:
	./$(FILE_OUT)