CC=gcc
CFLAGS=-std=c99 -pedantic -Werror -Wall -Wextra -Wvla

ARG= httpd.o

library: $(ARG)
	ar -csr libhttpd.a $(ARG)

all: CFLAGS+=-fsanitize=address -g
all:
	$(CC) $(CFLAGS) -o test test.c httpd.c

clean:
	$(RM) $(ARG) libhttpd.a test
