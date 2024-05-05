#include <stdlib.h>

#include "my_c_tail.h"

int main(int argc, char *argv[])
{
    if (argc > 1)
        stdintail(atoi(argv[1]));
    return 0;
}
