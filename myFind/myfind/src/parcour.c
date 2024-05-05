#define _DEFAULT_SOURCE

#include <dirent.h>
#include <errno.h>
#include <libgen.h>
#include <string.h>
#include <sys/stat.h>

#include "my_find.h"

static int pas_point_et_pas_point_point(const char *name)
{
    return (strcmp(name, ".") != 0 && strcmp(name, "..") != 0);
}

static char *modif(const char *path, const char *ajout)
{
    int tp = strlen(path);
    int ta = strlen(ajout);
    char *new_path = malloc(sizeof(char) * tp + ta + 2);
    strcpy(new_path, path);
    new_path[tp] = '/';
    for (int i = tp + 1, compte = 0; i <= tp + ta + 1; i++, compte++)
    {
        new_path[i] = ajout[compte];
    }
    return new_path;
}

static int error(struct info *info, DIR *stream)
{
    if (stream == NULL)
    {
        return 0;
    }
    else
    {
        closedir(stream);
        info->erreur = 1;
        return 1;
    }
}

char *checkslash(char *path)
{
    int tp = strlen(path);
    if (path[tp - 1] == '/')
    {
        errno = 1;
        path[tp - 1] = '\0';
    }
    return path;
}

int is_lnk(char *path)
{
    struct stat stat_p;
    if (lstat(path, &stat_p) == -1)
    {
        return 0;
    }
    if (S_ISLNK(stat_p.st_mode))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int parcourP(struct info *info, struct ast *ast, char *path, test list_t[])
{
    errno = 0;
    if (ast != NULL && evaluate(ast, path, list_t) && info->action == -1)
    {
        printf("%s\n", path);
    }
    else if (ast == NULL)
    {
        printf("%s\n", path);
    }
    if (is_lnk(path))
    {
        return 0;
    }
    path = checkslash(path);
    DIR *stream = opendir(path);
    if (stream == NULL)
    {
        return error(info, stream);
    }
    struct dirent *dir;
    char *new_path = NULL;
    while ((dir = readdir(stream)) != NULL)
    {
        if (pas_point_et_pas_point_point(dir->d_name))
        {
            if (dir->d_type == DT_DIR)
            {
                new_path = modif(path, dir->d_name);
                if (parcourP(info, ast, new_path, list_t) == 1)
                {
                    free(new_path);
                    closedir(stream);
                    return 1;
                }
                free(new_path);
            }
            else
            {
                new_path = modif(path, dir->d_name);
                if (ast != NULL && evaluate(ast, new_path, list_t)
                    && info->action == -1)
                {
                    printf("%s\n", new_path);
                }
                else if (ast == NULL)
                {
                    printf("%s\n", new_path);
                }
                free(new_path);
            }
        }
        if (errno != 0)
        {
            return error(info, stream);
        }
    }
    closedir(stream);
    return 0;
}

int parcourD(struct info *info, struct ast *ast, char *path, test list_t[])
{
    errno = 0;
    path = checkslash(path);
    int a = errno;
    errno = 0;
    if (is_lnk(path))
    {
        if (a == 1)
        {
            printf("%s/\n", path);
        }
        else
        {
            printf("%s\n", path);
        }
        return 0;
    }
    DIR *stream = opendir(path);
    if (stream == NULL)
    {
        return error(info, stream);
    }
    struct dirent *dir;
    char *new_path = NULL;
    while ((dir = readdir(stream)) != NULL)
    {
        if (pas_point_et_pas_point_point(dir->d_name))
        {
            if (dir->d_type == DT_DIR)
            {
                new_path = modif(path, dir->d_name);
                if (parcourD(info, ast, new_path, list_t) == 1)
                {
                    free(new_path);
                    closedir(stream);
                    return 1;
                }
                free(new_path);
            }
            else
            {
                new_path = modif(path, dir->d_name);
                if (ast != NULL && evaluate(ast, new_path, list_t)
                    && info->action == -1)
                {
                    printf("%s\n", new_path);
                }
                else if (ast == NULL)
                {
                    printf("%s\n", new_path);
                }
                free(new_path);
            }
        }
        if (errno != 0)
        {
            return error(info, stream);
        }
    }
    if (ast != NULL && evaluate(ast, path, list_t) && info->action == -1)
    {
        if (a == 1)
        {
            printf("%s/\n", path);
        }
        else
        {
            printf("%s\n", path);
        }
    }
    else if (ast == NULL)
    {
        if (a == 1)
        {
            printf("%s/\n", path);
        }
        else
        {
            printf("%s\n", path);
        }
    }
    closedir(stream);
    return 0;
}

static int gestion_SLINK(struct dirent *dir, char *path)
{
    if (DT_LNK != dir->d_type)
    {
        return 0;
    }
    else
    {
        char *new_path = modif(path, dir->d_name);
        DIR *stream = opendir(new_path);
        if (stream == NULL)
        {
            errno = 0;
            free(new_path);
            return 0;
        }
        else
        {
            free(new_path);
            closedir(stream);
            return 1;
        }
    }
}

int parcourL(struct info *info, struct ast *ast, char *path, test list_t[])
{
    errno = 0;
    path = dirname(path);
    if (ast != NULL && evaluate(ast, path, list_t) && info->action == -1)
    {
        printf("%s\n", path);
    }
    else if (ast == NULL)
    {
        printf("%s\n", path);
    }
    path = checkslash(path);
    DIR *stream = opendir(path);
    if (stream == NULL)
    {
        return error(info, stream);
    }
    struct dirent *dir;
    char *new_path = NULL;
    while ((dir = readdir(stream)) != NULL)
    {
        if (pas_point_et_pas_point_point(dir->d_name))
        {
            if (dir->d_type == DT_DIR || gestion_SLINK(dir, path))
            {
                new_path = modif(path, dir->d_name);
                if (parcourL(info, ast, new_path, list_t) == 1)
                {
                    free(new_path);
                    closedir(stream);
                    return 1;
                }
                free(new_path);
            }
            else
            {
                new_path = modif(path, dir->d_name);
                if (ast != NULL && evaluate(ast, new_path, list_t)
                    && info->action == -1)
                {
                    printf("%s\n", new_path);
                }
                else if (ast == NULL)
                {
                    printf("%s\n", new_path);
                }
                free(new_path);
            }
        }
        if (errno != 0)
        {
            return error(info, stream);
        }
    }
    closedir(stream);
    return 0;
}

int parcourH(struct info *info, struct ast *ast, char *path, test list_t[])
{
    errno = 0;
    if (ast != NULL && evaluate(ast, path, list_t) && info->action == -1)
    {
        printf("%s\n", path);
    }
    else if (ast == NULL)
    {
        printf("%s\n", path);
    }
    path = checkslash(path);
    DIR *stream = opendir(path);
    if (stream == NULL)
    {
        return error(info, stream);
    }
    struct dirent *dir;
    char *new_path = NULL;
    while ((dir = readdir(stream)) != NULL)
    {
        if (pas_point_et_pas_point_point(dir->d_name))
        {
            if (dir->d_type == DT_DIR)
            {
                new_path = modif(path, dir->d_name);
                if (parcourP(info, ast, new_path, list_t) == 1)
                {
                    free(new_path);
                    closedir(stream);
                    return 1;
                }
                free(new_path);
            }
            else
            {
                new_path = modif(path, dir->d_name);
                if (ast != NULL && evaluate(ast, new_path, list_t)
                    && info->action == -1)
                {
                    printf("%s\n", new_path);
                }
                else if (ast == NULL)
                {
                    printf("%s\n", new_path);
                }
                free(new_path);
            }
        }
        if (errno != 0)
        {
            return error(info, stream);
        }
    }
    closedir(stream);
    return 0;
}
