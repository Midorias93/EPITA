#include <stdio.h>

void grade(char g)
{
    switch (g)
    {
    case 'A':
        puts("Excellent");
        break;
    case 'B':
        puts("Good");
        break;
    case 'C':
        puts("Not so bad");
        break;
    case 'D':
        puts("Could be worse");
        break;
    case 'E':
        puts("Maybe next time");
        break;
    case 'F':
        puts("No comment");
        break;
    default:
        puts("Call a wild ACU");
    }
}
