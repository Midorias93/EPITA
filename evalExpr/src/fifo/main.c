#include <stdio.h>

#include "fifo.h"

int main(void)
{
    struct fifo *test = fifo_init();
    printf("%ld\n", fifo_size(test));
    return 0;
}
