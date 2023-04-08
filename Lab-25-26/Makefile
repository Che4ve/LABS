CC = gcc
DEGUGGER = gdb
CFLAGS = -std=c17 -Wall
FILE_OUT = tree.out
SOURCES = queue.c myqueue.c

all:
	$(CC) $(CFLAGS) $(SOURCES) -o $(FILE_OUT)
	./$(FILE_OUT)
	rm -f $(FILE_OUT)
clean:
	rm -f *.out
	rm -f a.exe
debug:
	$(CC) $(CFLAGS) -g $(SOURCES) 
	sudo $(DEGUGGER) $(FILE_OUT)
comp:
	$(CC) $(CFLAGS) $(SOURCES) -o $(FILE_OUT)
run:
	./$(FILE_OUT)