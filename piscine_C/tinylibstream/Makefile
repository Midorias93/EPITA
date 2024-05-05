CC=gcc
CFLAGS=-std=c99 -pedantic -Werror -Wall -Wextra -Wvla
OBJ=src/tinylibstream.o

library: $(OBJ)
	 ar -csr libstream.a $(OBJ)

clean:
	$(RM) $(OBJ) libstream.a
