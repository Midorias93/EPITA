CC=gcc
CFLAGS=-std=c99 -pedantic -Werror -Wall -Wextra -Wvla -g

ARG=test.o

all: $(ARG)
	$(CC) -o main $(ARG) -fsanitize=address

point_o: $(ARG)

