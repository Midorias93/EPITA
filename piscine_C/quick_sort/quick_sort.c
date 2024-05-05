#include <stdio.h>

void swap(int *a, int *b)
{
    int save = *a;
    *a = *b;
    *b = save;
}

int partition(int *list, int begin, int end)
{
    int pivot = list[end];
    int i = begin - 1;
    for (int j = begin; j <= end - 1; j++)
    {
        if (list[j] <= pivot)
        {
            i++;
            swap(&list[i], &list[j]);
        }
    }
    swap(&list[i + 1], &list[end]);
    return i + 1;
}

static int *aux_quicksort(int list[], int begin, int end)
{
    if (begin <= end || begin < 0)
    {
        int pivot = partition(list, begin, end);
        aux_quicksort(list, begin, pivot - 1);
        aux_quicksort(list, pivot + 1, end);
    }
    return list;
}

void quicksort(int *tab, int len)
{
    if (len == 0 || len == 1)
    {
        return;
    }
    tab = aux_quicksort(tab, 0, len - 1);
}
