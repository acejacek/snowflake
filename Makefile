CC = gcc
CFLAGS = -std=c99
LFLAGS = -lraylib -lm

BINARY = snowflake

all: main.c
	$(CC) -o $(BINARY) main.c $(CFLAGS) $(LFLAGS)

debug: main.c
	$(CC) -o $(BINARY) main.c $(CFLAGS) $(LFLAGS) -ggdb

run: all
	./$(BINARY)

