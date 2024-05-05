CC=gcc
CFLAGS=-std=c99 -pedantic -Werror -Wall -Wextra -Wvla

ARG= server.o \
	 socket.o \
	 arg.o \


library: $(ARG)
	ar -csr libserver.a $(ARG)

myfind: fait
	$(CC) -o main $(ARG)

fait: $(ARG)

fait_test: CFLAGS+=-g
fait_test: $(ARG)


test: fait_test
	$(CC) -o main_test $(ARG) -fsanitize=address;

clean:
	$(RM) $(ARG) libserver.a
