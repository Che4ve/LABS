CC = gcc
CFLAGS = -std=c17
PARAMS = S:/Git/labs/KP-6/info.txt

GLOBALS = src/studentpc.c src/dict.c src/globals.c

MAIN_SRC = src/main.c $(GLOBALS)
MAIN_OUT = main.out

GEN_SRC = src/generate.c $(GLOBALS) 
GEN_OUT = gen.out

CONV_SRC = src/convert.c $(GLOBALS) 
CONV_OUT = conv.out



all: 
	$(CC) $(CFLAGS) $(MAIN_SRC) -o $(MAIN_OUT)
	$(CC) $(GEN_SRC) -o $(GEN_OUT)
	$(CC) $(CONV_SRC) -o $(CONV_OUT)

print:    io.o
	$(CC) $^ -o $@

execute:  gen.out conv.out main.out
	$(CC) $< -o $@

generate: 
	$(CC) $(GEN_SRC) -o $(GEN_OUT)

convert:
	$(CC) $(CONV_SRC) -o $(CONV_OUT)

clean:
	rm -f *.out
