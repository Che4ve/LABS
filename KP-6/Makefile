CC = gcc
CFLAGS = -std=c17 -Wall

GLOBALS = src/studentpc.c src/dict.c src/globals.c

MAIN_SRC = src/main.c $(GLOBALS)
MAIN_OUT = main.out

GEN_SRC = src/generate.c $(GLOBALS) 
GEN_OUT = gen.out

CONV_SRC = src/convert.c $(GLOBALS) 
CONV_OUT = conv.out

all: 
	$(CC) $(CFLAGS) $(MAIN_SRC) -o $(MAIN_OUT)
	$(CC) $(CFLAGS) $(GEN_SRC) -o $(GEN_OUT)
	$(CC) $(CFLAGS) $(CONV_SRC) -o $(CONV_OUT)

generate: 
	$(CC) $(CFLAGS) $(GEN_SRC) -o $(GEN_OUT)

convert:
	$(CC) $(CFLAGS) $(CONV_SRC) -o $(CONV_OUT)

debug: 
	$(CC) -g $(CFLAGS) $(MAIN_SRC) -o $(MAIN_OUT)
	$(CC) -g $(CFLAGS) $(GEN_SRC) -o $(GEN_OUT)
	$(CC) -g $(CFLAGS) $(CONV_SRC) -o $(CONV_OUT)

clean:
	rm -f *.out
