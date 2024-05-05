CC=gcc
CFLAGS=-std=c99 -pedantic -Werror -Wall -Wextra -Wvla
OBJ=vector_operation.o vector_init_destroy.o vector_affichage.o

test:
	$(CC) -g -fsanitize=address vector_operation.c vector_init_destroy.c vector_affichage.c main.c
	./a.out


library: $(OBJ)
	ar -csr libvector.a $(OBJ)

clean:
	$(RM) *.o *.a
