.PHONY: all clean

CC = gcc
CFLAGS = -Wall -Wextra -std=c11
OBJS = main.o card.o deck.o blackjack.o
DEPS = $(OBJS:.o=.d)  # e.g., main.d, card.d, etc.

-include $(DEPS)

all: gamblingc

gamblingc: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile .c -> .o AND generate .d dependency file
%.o: %.c
	$(CC) $(CFLAGS) -MMD -c $< -o $@

clean:
	rm -f *.o *.d gamblingc