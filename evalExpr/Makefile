CC=gcc
CFLAGS=-std=c99 -pedantic -Werror -Wall -Wextra -Wvla

FIFO=./src/fifo/fifo_access.o ./src/fifo/fifo_setup_destroy.o

STACK=./src/stack/stack.o

TOKEN=./src/token/token.o

stack: $(STACK)

fifo: $(FIFO)

token: $(TOKEN)

evalexpr.o: ./src/evalexpr.o

main.o: ./src/main.o

all:evalexpr.o stack fifo main.o token
	$(CC) -o evalexpr $(FIFO) $(STACK) $(TOKEN) ./src/evalexpr.o ./src/main.o

check:evalexpr.o stack fifo main.o token
	$(CC) -fsanitize=address -o evalexpr $(FIFO) $(STACK) $(TOKEN) ./src/evalexpr.o ./src/main.o


clean:
	$(RM) $(FIFO) $(STACK) $(TOKEN) ./src/evalexpr.o evalexpr ./src/main.o

.PHONY: clean all stack fifo token
