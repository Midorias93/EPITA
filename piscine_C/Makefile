CC=gcc
F=-std=c99 -pedantic -Werror -Wall -Wextra -Wvla -fPIC --coverage
LDLIBS=-lcriterion -lgcov

all: levenshtein.o
	$(CC) -o levenshtein levenshtein.o

levenshtein.o: ./src/levenshtein.c
	$(CC) $(F) -c -o levenshtein.o levenshtein.c

levenshtein_test.o: ./tests/levenshtein_test.c
	$(CC) $(CLFLAGS) -c -o levenshtein_test.o levenshtein_test.c

check:levenshtein_test.o levenshtein.o

debug:levenshtein.o main.o
	$(CC) 

gvoc: levenshtein_test.o levenshtein.o
	$(CC) --coverage -o levenshtein_test levenshtein_test.o levenshtein.o $(LDLIBS) -lgcov
	./levenshtein_test
	gcovr --html --html-nested --output=report.html

clen:
	$(RM) levenshtein levenshtein_test *.o *.html
	$(RM) *.gcda *.gcno
