#include <stdlib.h>

#include "dlist.h"

void dlist_shift(struct dlist *list, int offset)
{
    if (list->size == 0)
    {
        return;
    }
    int ajout = 0;
    if (offset < 0)
    {
        for (int i = 0; i < -offset; i++)
        {
            ajout = dlist_remove_at(list, 0);
            dlist_push_back(list, ajout);
        }
    }
    else
    {
        for (int i = 0; i < offset; i++)
        {
            ajout = dlist_remove_at(list, list->size - 1);
            dlist_push_front(list, ajout);
        }
    }
}

int dlist_add_sort(struct dlist *list, int element)
{
    if (list->size == 0)
    {
        dlist_push_front(list, element);
        return 1;
    }
    if (element < 0)
    {
        return -1;
    }
    else
    {
        struct dlist_item *save = list->head;
        size_t indice = 0;
        while (indice < list->size && save->data < element)
        {
            indice++;
            save = save->next;
        }
        dlist_insert_at(list, element, indice);
    }
    return 1;
}

int dlist_remove_eq(struct dlist *list, int element)
{
    if (element < 0)
    {
        return 0;
    }
    else
    {
        struct dlist_item *save = list->head;
        size_t indice = 0;
        while (indice < list->size && save->data != element)
        {
            indice++;
            save = save->next;
        }
        if (indice < list->size)
        {
            dlist_remove_at(list, indice);
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

struct dlist *dlist_copy(const struct dlist *list)
{
    struct dlist *copy = dlist_init();
    if (list->size == 0)
    {
        return copy;
    }
    struct dlist_item *save = list->head;
    while (save->next != NULL)
    {
        dlist_push_back(copy, save->data);
        save = save->next;
    }
    dlist_push_back(copy, save->data);
    return copy;
}

static void swap(int *a, int *b)
{
    int save = *a;
    *a = *b;
    *b = save;
}

void dlist_sort(struct dlist *list)
{
    if (list->size == 0)
    {
        return;
    }
    for (struct dlist_item *save = list->tail; save != NULL; save = save->prev)
    {
        for (struct dlist_item *save2 = save; save2->next != NULL;
             save2 = save2->next)
        {
            if (save2->next->data < save2->data)
            {
                swap(&save2->next->data, &save2->data);
            }
        }
    }
}

void dlist_merge(struct dlist *list1, struct dlist *list2)
{
    dlist_concat(list1, list2);
    dlist_sort(list1);
}

static size_t max(size_t a, size_t b)
{
    size_t max = a;
    max = (max < b) ? b : max;
    return max;
}

static size_t min3(size_t a, size_t b, size_t c)
{
    size_t min = a;
    min = (min > b) ? b : min;
    min = (min > c) ? c : min;
    return min;
}

static size_t min2(size_t a, size_t b)
{
    size_t min = a;
    min = (min > b) ? b : min;
    return min;
}

static size_t str_len(const char *str)
{
    size_t taille = 0;
    while (str[taille] != '\0')
    {
        taille++;
    }
    return taille;
}

static size_t levenshtein(const char *s1, const char *s2)
{
    if (min2(str_len(s1), str_len(s2)) == 0)
    {
        return max(str_len(s1), str_len(s2));
    }
    else if (s1[0] == s2[0])
    {
        return levenshtein(s1 + 1, s2 + 1);
    }
    else
    {
        return 1
            + min3(levenshtein(s1 + 1, s2), levenshtein(s1, s2 + 1),
                   levenshtein(s1 + 1, s2 + 1));
    }
}

unsigned int dlist_levenshtein(struct dlist *list1, struct dlist *list2)
{
    char *dlist1 = malloc(sizeof(char) * list1->size + 1);
    char *dlist2 = malloc(sizeof(char) * list2->size + 1);
    struct dlist_item *save = list1->head;
    for (size_t i = 0; i < list1->size; i++)
    {
        dlist1[i] = save->data;
        save = save->next;
    }
    dlist1[list1->size] = '\0';
    save = list2->head;
    for (size_t i = 0; i < list2->size; i++)
    {
        dlist2[i] = save->data;
        save = save->next;
    }
    dlist2[list2->size] = '\0';
    const char *l1 = dlist1;
    const char *l2 = dlist2;
    size_t resultat = levenshtein(l1, l2);
    free(dlist1);
    free(dlist2);
    return resultat;
}
