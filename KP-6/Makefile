CC = gcc
CFLAGS = -std=c17 -Wall -Werror
FILE_OUT = kp6.out
SOURCES = src/main.c src/studentpc.c src/dict.c

all:
	$(CC) $(CFLAGS) $(SOURCES) -o $(FILE_OUT)
	./$(FILE_OUT)
	rm -f $(FILE_OUT)

print:    io.o
	$(CC) $^ -o $@

execute:  io.o execute.o student.o
	$(CC) $^ -o $@

clean:
	rm -f *.o

generate: generate.o io.o
	$(CC) $^ -o $@

cleanall:
	rm -f execute generate *.o

