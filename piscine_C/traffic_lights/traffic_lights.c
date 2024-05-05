void init(unsigned char *lights)
{
    unsigned char a = 0;
    *lights = *lights & a;
}

void turn_on(unsigned char *lights, unsigned char light_num)
{
    unsigned char a = 1 << (light_num - 1);
    *lights = *lights | a;
}

void turn_off(unsigned char *lights, unsigned char light_num)
{
    unsigned char a = ~(1 << (light_num - 1));
    *lights = *lights & a;
}

static unsigned char rol(unsigned char value, unsigned char rol)
{
    unsigned char mask = 0;
    mask = value;
    mask = mask >> (4 - (rol % 4));
    value = value << (rol % 4);
    value = (value | mask);
    return value;
}
void next_step(unsigned char *lights)
{
    *lights = rol(*lights, 1);
}

void reverse(unsigned char *lights)
{
    unsigned char a = 255;
    *lights = *lights ^ a;
}

void swap(unsigned char *lights_1, unsigned char *lights_2)
{
    if (*lights_1 == *lights_2)
    {
        return;
    }
    *lights_1 = *lights_1 ^ *lights_2;
    *lights_2 = *lights_1 ^ *lights_2;
    *lights_1 = *lights_1 ^ *lights_2;
}
