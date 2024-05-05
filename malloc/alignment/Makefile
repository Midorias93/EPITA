CC=gcc
FLAGS=-std=c99 -pedantic -Werror -Wall -Wextra -Wvla

ARG= alignment.o


myfind: fait
	$(CC) -o main $(ARG)

fait: $(ARG)

fait_test: CFLAGS+=-g
fait_test: $(ARG)


test: fait_test
	$(CC) -o main_test $(ARG) -fsanitize=address;

clean:
	$(RM) $(ARG) main_test main
