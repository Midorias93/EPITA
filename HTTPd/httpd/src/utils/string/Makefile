CC=gcc
CFLAGS=-std=c99 -Werror -Wall -Wextra -Wvla -pedantic

ARG=string.o

library: $(ARG)
	ar -csr libstring.a $(ARG)

clean:
	$(RM) $(ARG) libstring.a
