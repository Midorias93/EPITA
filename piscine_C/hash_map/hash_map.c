#include "hash_map.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct hash_map *hash_map_init(size_t size)
{
    struct hash_map *new_hash_map = malloc(sizeof(struct hash_map));
    new_hash_map->size = size;
    struct pair_list **new_pair_list =
        malloc(sizeof(struct pair_list *) * size);
    for (size_t i = 0; i < size; i++)
    {
        new_pair_list[i] = NULL;
    }
    new_hash_map->data = new_pair_list;
    return new_hash_map;
}

static bool cherche_et_change(struct pair_list *list, const char *key,
                              char *value)
{
    if (list == NULL)
    {
        return 0;
    }
    if (!strcmp(list->key, key))
    {
        list->value = value;
        return 1;
    }
    struct pair_list *save = list;
    while (save->next != NULL)
    {
        if (!strcmp(save->key, key))
        {
            save->value = value;
            return 1;
        }
        save = save->next;
    }
    return 0;
}

static struct pair_list *ajout(struct pair_list *list, const char *key,
                               char *value)
{
    struct pair_list *n_l = malloc(sizeof(struct pair_list));
    n_l->key = key;
    n_l->value = value;
    n_l->next = list;
    return n_l;
}

bool hash_map_insert(struct hash_map *hash_map, const char *key, char *value,
                     bool *updated)
{
    if (hash_map == NULL || hash_map->size == 0)
    {
        return 0;
    }
    else
    {
        int indice = hash(key) % hash_map->size;
        *updated = cherche_et_change(hash_map->data[indice], key, value);
        if (*updated == 1)
        {
            return 1;
        }
        else
        {
            hash_map->data[indice] = ajout(hash_map->data[indice], key, value);
            return 1;
        }
    }
}

static void free_list(struct pair_list *list)
{
    if (list == NULL)
    {
        return;
    }
    if (list->next != NULL)
    {
        free_list(list->next);
    }
    free(list);
}

void hash_map_free(struct hash_map *hash_map)
{
    if (hash_map == NULL)
    {
        return;
    }
    for (size_t i = 0; i < hash_map->size; i++)
    {
        free_list(hash_map->data[i]);
    }
    free(hash_map->data);
    free(hash_map);
}

static void display_list(struct pair_list *list)
{
    struct pair_list *save = list;
    while (save->next != NULL)
    {
        printf("%s: %s, ", save->key, save->value);
        save = save->next;
    }
    printf("%s: %s\n", save->key, save->value);
}

void hash_map_dump(struct hash_map *hash_map)
{
    for (size_t i = 0; i < hash_map->size; i++)
    {
        if (hash_map->data[i] != NULL)
        {
            display_list(hash_map->data[i]);
        }
    }
}

const char *hash_map_get(const struct hash_map *hash_map, const char *key)
{
    if (hash_map == NULL || hash_map->size == 0)
    {
        return NULL;
    }
    int i = hash(key) % hash_map->size;
    struct pair_list *list = hash_map->data[i];
    if (list == NULL)
    {
        return NULL;
    }
    if (!strcmp(list->key, key))
    {
        return list->value;
    }
    while (list->next != NULL)
    {
        if (!strcmp(list->key, key))
        {
            return list->value;
        }
        list = list->next;
    }
    if (!strcmp(list->key, key))
    {
        return list->value;
    }
    return NULL;
}

static bool my_remove(struct pair_list *list, const char *key)
{
    struct pair_list *save = list->next;
    if (save == NULL)
    {
        return 0;
    }
    struct pair_list *precedent = list;
    while (save->next != NULL)
    {
        if (!strcmp(save->key, key))
        {
            precedent->next = save->next;
            free(save);
            return 1;
        }
        precedent = save;
        save = save->next;
    }
    if (!strcmp(save->key, key))
    {
        precedent->next = save->next;
        free(save);
        return 1;
    }
    return 0;
}

bool hash_map_remove(struct hash_map *hash_map, const char *key)
{
    if (hash_map == NULL || hash_map->size == 0)
    {
        return 0;
    }
    int i = hash(key) % hash_map->size;
    if (hash_map->data[i] == NULL)
    {
        return 0;
    }
    else if (!strcmp(hash_map->data[i]->key, key))
    {
        struct pair_list *save = hash_map->data[i]->next;
        free(hash_map->data[i]);
        hash_map->data[i] = save;
        return 1;
    }
    else
    {
        return my_remove(hash_map->data[i], key);
    }
}
