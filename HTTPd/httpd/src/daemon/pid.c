#define _POSIX_C_SOURCE 200809L

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "daemon.h"

int get_pid(char *path_pid_file)
{
    FILE *stream = fopen(path_pid_file, "r");
    if (stream == NULL)
    {
        return 0;
    }
    char *char_pid = NULL;
    size_t size_char_pid = 0;
    size_t size_pid = getline(&char_pid, &size_char_pid, stream);
    int pid = 0;
    if (size_pid > 0)
    {
        pid = atoi(char_pid);
    }
    free(char_pid);
    fclose(stream);
    return pid;
}

void sauv_pid(char *path_pid_file, int pid)
{
    FILE *stream = fopen(path_pid_file, "w");
    if (stream == NULL)
    {
        return;
    }
    char *char_pid = malloc(sizeof(char) * 10);
    char_pid = my_itoa(pid, char_pid);
    size_t size_pid = strlen(char_pid);
    char_pid[size_pid++] = '\n';
    fwrite(char_pid, sizeof(char), size_pid, stream);
    free(char_pid);
    fclose(stream);
}

int is_deamon_a_life(int pid)
{
    if (pid == 0 || kill(pid, 0) == -1)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
