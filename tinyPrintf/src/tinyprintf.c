#include "tinyprintf.h"

static int taille_int(int n)
{
    int taille = 1;
    while (n / 10 != 0)
    {
        taille++;
        n /= 10;
    }
    return taille;
}

static char *my_itoa(int value, char *s)
{
    int i = 0;
    int sauv = 0;
    char retenu;
    if (value < 0)
    {
        value = -value;
        sauv++;
    }
    while (value / 10 != 0)
    {
        s[i] = (value % 10) + '0';
        value = value / 10;
        i++;
    }
    s[i] = value + '0';
    if (sauv == 1)
    {
        i++;
        s[i] = '-';
    }
    int taille = i;
    i = 0;
    while (i <= taille / 2)
    {
        retenu = s[taille - i];
        s[taille - i] = s[i];
        s[i] = retenu;
        i++;
    }
    taille++;
    s[taille] = '\0';
    return s;
}

static char *my_itoa_base(unsigned int n, char *s, const char *base)
{
    unsigned int taille_base = 0;
    int i = 0;
    while (base[taille_base] != '\0')
    {
        taille_base++;
    }
    while (n / taille_base != 0)
    {
        s[i] = base[n % taille_base];
        i++;
        n = n / taille_base;
    }
    s[i] = base[n % taille_base];
    int taille = i;
    char retenu;
    i = 0;
    while (i <= taille / 2)
    {
        retenu = s[taille - i];
        s[taille - i] = s[i];
        s[i] = retenu;
        i++;
    }
    taille++;
    s[taille] = '\0';
    return s;
}

int tinyprintf(const char *format, ...)
{
    if (format == NULL)
    {
        return 0;
    }
    int nombre_car = 0;
    va_list arg;
    char *str;
    char c;
    int val = 0;
    unsigned int u_val = 0;
    int index = 0;
    va_start(arg, format);
    while (*format != '\0')
    {
        if (*format == '%')
        {
            format++;
            switch (*format)
            {
            case '%':
                putchar('%');
                nombre_car++;
                format++;
                break;
            case 's':
                str = va_arg(arg, char *);
                while (*str != '\0')
                {
                    putchar(*str);
                    nombre_car++;
                    str++;
                }
                format++;
                break;
            case 'd':
                val = va_arg(arg, int);
                str = malloc(sizeof(char) * (taille_int(val)) + 1);
                str = my_itoa(val, str);
                while (str[index] != '\0')
                {
                    putchar(str[index]);
                    nombre_car++;
                    index++;
                }
                index = 0;
                free(str);
                format++;
                break;
            case 'c':
                c = va_arg(arg, int);
                putchar(c);
                nombre_car++;
                format++;
                break;
            case 'o':
                u_val = va_arg(arg, unsigned int);
                str = malloc(sizeof(char) * (taille_int(u_val) + 1));
                str = my_itoa_base(u_val, str, "01234567");
                while (str[index] != '\0')
                {
                    putchar(str[index]);
                    nombre_car++;
                    index++;
                }
                index = 0;
                free(str);
                format++;
                break;
            case 'x':
                u_val = va_arg(arg, unsigned int);
                str = malloc(sizeof(char) * (taille_int(u_val) + 1));
                str = my_itoa_base(u_val, str, "0123456789abcdef");
                while (str[index] != '\0')
                {
                    putchar(str[index]);
                    nombre_car++;
                    index++;
                }
                index = 0;
                free(str);
                format++;
                break;
            case 'u':
                u_val = va_arg(arg, unsigned int);
                str = malloc(sizeof(char) * (taille_int(u_val) + 1));
                str = my_itoa_base(u_val, str, "0123456789");
                while (str[index] != '\0')
                {
                    putchar(str[index]);
                    nombre_car++;
                    index++;
                }
                index = 0;
                free(str);
                format++;
                break;
            default:
                putchar('%');
                putchar(*format);
                nombre_car += 2;
                format++;
                break;
            }
        }
        else
        {
            putchar(*format);
            nombre_car++;
            format++;
        }
    }
    return nombre_car;
}
