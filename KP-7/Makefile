CC = gcc
CFLAGS = -std=c17

LIBS = spmatrix.c

MAIN_SRC = main.c 
MAIN_OUT = main.out

all:
	$(CC) $(CFLAGS) $(MAIN_SRC) $(LIBS) -o $(MAIN_OUT)

debug: 
	$(CC) -g $(MAIN_SRC) $(LIBS) -o $(MAIN_OUT)

clean:
	rm -f *.out