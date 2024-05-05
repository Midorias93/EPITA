#include <stdio.h>
#include <sys/stat.h>

int simple_stat(char *path)
{
    struct stat stat_file;
    if (stat(path, &stat_file) == -1)
    {
        fprintf(stderr, "simple_stat: impossible de lire le fichier.\n");
        return 1;
    }
    else
    {
        printf("st_dev=%ld\n", stat_file.st_dev);
        printf("st_ino=%ju\n", stat_file.st_ino);
        printf("st_mode=0%o\n", stat_file.st_mode);
        printf("st_nlink=%ld\n", stat_file.st_nlink);
        printf("st_uid=%u\n", stat_file.st_uid);
        printf("st_gid=%u\n", stat_file.st_gid);
        printf("st_rdev=%ld\n", stat_file.st_rdev);
        printf("st_size=%ld\n", stat_file.st_size);
        printf("st_atime=%ld\n", stat_file.st_atime);
        printf("st_mtime=%ld\n", stat_file.st_mtime);
        printf("st_ctime=%ld\n", stat_file.st_ctime);
        printf("st_blksize=%ld\n", stat_file.st_blksize);
        printf("st_blocks=%ld\n", stat_file.st_blocks);
    }
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            if (simple_stat(argv[i]) == 1)
            {
                return 1;
            }
        }
    }
    return 0;
}
