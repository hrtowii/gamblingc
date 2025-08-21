.PHONY: all clean

CC = gcc
CFLAGS = -Wall -Wextra -std=c11
OBJS = main.o card.o deck.o

all: gamblingc

gamblingc: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c card.h deck.h
	$(CC) $(CFLAGS) -c main.c

card.o: card.c card.h
	$(CC) $(CFLAGS) -c card.c

deck.o: deck.c deck.h card.h
	$(CC) $(CFLAGS) -c deck.c

clean:
	rm -rf *.o gamblingc