CC = gcc
DEGUGGER = gdb
CFLAGS = -std=c11 -Wall -Werror
FILE_OUT = tree.out
SOURCES = mytree.c

all:
	$(CC) $(CFLAGS) $(SOURCES) -o $(FILE_OUT)
	./$(FILE_OUT)
	rm -f $(FILE_OUT)
clean:
	rm -f *.out
debug:
	$(CC) $(CFLAGS) -g $(SOURCES) 
	sudo $(DEGUGGER) $(FILE_OUT)
comp:
	$(CC) $(CFLAGS) $(SOURCES) -o $(FILE_OUT)
run:
	./$(FILE_OUT)