CC=gcc
CFLAGS=-std=c99 -Werror -pedantic -Wall -Wextra -Wvla
LDLIBS=-lcriterion

ARG=size.o height.o parcour.o is_full.o is_perfect.o is_complete.o is_degenerate.o is_bst.o

library: $(ARG)
	ar -csr libbinary_tree.a $(ARG)

clean:
	$(RM) *.o *.a


