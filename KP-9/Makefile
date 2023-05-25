CC = gcc
CFLAGS = -std=c17

PARAMETERS = data.txt

LIBS = poemsort.c

MAIN_SRC = main.c 
MAIN_OUT = main.out

all:
	$(CC) $(CFLAGS) $(MAIN_SRC) $(LIBS) -o $(MAIN_OUT)

debug: 
	$(CC) -g $(MAIN_SRC) $(LIBS) -o $(MAIN_OUT)

run:
	./$(MAIN_OUT) $(PARAMETERS)

clean:
	rm -f *.out