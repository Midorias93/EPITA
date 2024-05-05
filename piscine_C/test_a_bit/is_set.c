unsigned int is_set(unsigned int value, unsigned char n)
{
    unsigned char mask = 1 << (n - 1);
    return (value & mask) != 0;
}
