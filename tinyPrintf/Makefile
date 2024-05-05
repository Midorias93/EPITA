CC=gcc
CFLAGS=-std=c99 -pedantic -Werror -Wall -Wextra -Wvla
LDLIBS=-lcriterion

all: tinyprintf.o
	$(CC) -o tinyprintf ./src/tinyprintf.o

tinyprintf.o: ./src/tinyprintf.c
	$(CC) $(CFLAGS) -c -o ./src/tinyprintf.o ./src/tinyprintf.c

tinyprintf_test.o: ./tests/tinyprintf_test.c
	$(CC) $(CLFLAGS) -c -o ./tests/tinyprintf_test.o tests/tinyprintf_test.c

check: tinyprintf_test.o tinyprintf.o
	$(CC) $(LDLIBS) -o tinyprintf_test ./tests/tinyprintf_test.o ./src/tinyprintf.o
	./tinyprintf_test

clean:
	$(RM) ./tinyprintf ./tinyprintf_test ./src/*.o ./tests/*.o
