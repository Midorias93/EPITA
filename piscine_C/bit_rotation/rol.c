#include <stdio.h>

unsigned char rol(unsigned char value, unsigned char rol)
{
    unsigned char mask = 0;
    mask = value;
    mask = mask >> (8 - (rol % 8));
    value = value << (rol % 8);
    value = (value | mask);
    return value;
}
