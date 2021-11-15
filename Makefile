CC := gcc
CFLAGS := -O -g -Wall -Werror -std=c99 -D_DEFAULT_SOURCE -D_BSD_SOURCE

all: testblocks

testblocks: wordblocks.o main.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f testblocks words.out *.o *~

.PHONY: all clean
