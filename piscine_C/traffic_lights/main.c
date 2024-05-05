#include <stdio.h>

#include "traffic_lights.h"

int main(void)
{
    unsigned char l = 6;
    turn_on(&l, 3);
    printf("%d\n", l);
}
