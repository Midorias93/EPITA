#include <stdio.h>

int count_words(const char *file_in);

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        printf("%d\n", count_words(argv[1]));
    }
}
