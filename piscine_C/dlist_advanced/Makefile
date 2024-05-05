CC=gcc
CFLAGS=-std=c99 -Werror -pedantic -Wall -Wextra -Wvla

ARG=dlist_opperation.o dlist_affichage_get.o dlist_modif.o dlist_init_destroy.o dlist_search.o dlist_advance.o

library: $(ARG)
	ar -csr libdlist.a $(ARG)

clean:
	$(RM) *.o *.a
