#define _DEFAULT_SOURCE

#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

int pas_point_et_pas_point_point(char *name)
{
    return strcmp(name, ".") != 0 && strcmp(name, "..") != 0;
}

int simple_ls(const char *path)
{
    errno = 0;
    if (path == NULL)
    {
        path = ".";
    }
    DIR *stream = opendir(path);
    if (stream == NULL)
    {
        fprintf(stderr, "simple_ls: %s: No such file or directory\n", path);
        return 1;
    }
    struct dirent *dir = readdir(stream);
    while (dir != NULL)
    {
        if (errno == 1)
        {
            fprintf(stderr, "simple_ls: un fichier na pas pu etre lu");
            return 1;
        }
        else if (pas_point_et_pas_point_point(dir->d_name))
        {
            printf("%s\n", dir->d_name);
        }
        dir = readdir(stream);
    }
    closedir(stream);
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        return simple_ls(argv[1]);
    }
    else if (argc == 1)
    {
        simple_ls(NULL);
    }
}
