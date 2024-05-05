#include <stdio.h>

#include "null_terminated_arrays.h"

int main(void)
{
    const char *array1[11] = { "twenty nine",
                               "twenty eight",
                               "twenty seven",
                               "twenty six",
                               "twenty five",
                               "twenty four",
                               "twenty three",
                               "twenty two",
                               "twenty one",
                               "twenty",
                               NULL };
    const char *array2[11] = { "nineteen", "eighteen", "seventeen", "sixteen",
                               "fifteen",  "fourteen", "thirteen",  "twelve",
                               "eleven",   "ten",      NULL };
    const char *array3[11] = { "nine", "eight", "seven", "six",
                               "five", "four",  "three", "two",
                               "one",  "zero",  NULL };
    const char **matrix[4] = { array1, array2, array3, NULL };
    reverse_matrix(matrix);
}
