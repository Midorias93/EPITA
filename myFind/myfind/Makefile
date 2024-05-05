CC=gcc
FLAGS=-std=c99 -pedantic -Werror -Wall -Wextra -Wvla

ARG= src/token/token.o \
	 src/parcour.o \
	 src/test.o \
	 src/fifo/fifo_access.o \
	 src/fifo/fifo_setup_destroy.o \
	 src/parchemin/parchemin.o \
	 src/AST/fifo_ast_setup_destroy.o \
	 src/AST/fifo_ast_access.o \
	 src/AST/ast.o \
	 src/stack/stack.o \
	 src/parsing.o \
	 src/gestion_type.o \
	 src/option.o \
	 src/my_find.o \
	 src/action.o



all: myfind

myfind: fait
	$(CC) -o myfind $(ARG)

fait: ARG+=src/my_find.o
fait: $(ARG)

fait_test: CFLAGS+=-g
fait_test: $(ARG)


test: fait_test
	$(CC) -o myfind_test $(ARG) -fsanitize=address;

clean:
	$(RM) $(ARG) myfind_test myfind tests/my_find_test
