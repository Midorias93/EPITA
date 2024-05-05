CC=gcc
CFLAGS=-std=c99 -pedantic -Werror -Wall -Wextra -Wvla
OBJ=fifo_setup_destroy.o fifo_access.o

library: $(OBJ)
	 ar -csr libfifo.a $(OBJ)

clean:
	$(RM) *.o *.a
