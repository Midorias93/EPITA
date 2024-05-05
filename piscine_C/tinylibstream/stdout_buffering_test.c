#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    const char test_string[] = "Robin\nloves\nBatman\n";
    for (size_t i = 0; test_string[i]; i++)
    {
        usleep(100000); // wait a tenth of a second
        putchar(test_string[i]);
    }
}
