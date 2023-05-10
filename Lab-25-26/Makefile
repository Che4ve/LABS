CC = gcc
DEGUGGER = gdb
CFLAGS = -std=c17 -Wall
FILE_OUT = tree.out
SOURCES = queue.c myqueue.c

all:
	$(CC) $(CFLAGS) $(SOURCES) -o $(FILE_OUT)

clean:
	rm -f *.out

debug:
	$(CC) $(CFLAGS) -g $(SOURCES) -o $(FILE_OUT)
	$(DEGUGGER) $(FILE_OUT)

comp:
	$(CC) $(CFLAGS) $(SOURCES) -o $(FILE_OUT)

run:
	./$(FILE_OUT)