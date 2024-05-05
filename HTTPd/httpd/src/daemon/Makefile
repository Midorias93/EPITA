CC=gcc
CFLAGS=-std=c99 -pedantic -Werror -Wall -Wextra -Wvla

ARG= option.o \
	 daemon.o \
	 my_itoa.o \
	 pid.o

library: $(ARG)
	ar -csr libdaemon.a $(ARG)

clean:
	$(RM) $(ARG) libdaemon.a
