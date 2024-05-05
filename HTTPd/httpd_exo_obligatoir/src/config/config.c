#define _POSIX_C_SOURCE 200809L

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static struct config *config_creator(void)
{
    struct config *config = malloc(sizeof(struct config));
    config->pid_file = NULL;
    config->log_file = NULL;
    config->log = 1;
    config->servers = NULL;
    config->nb_servers = 0;
    return config;
}

static struct config *assign_config(struct config *config, FILE *stream)
{
    char *buffer = NULL;
    size_t size_buffer = 0;
    ssize_t size_line = 0;
    char *save_buffer = NULL;
    char *save = NULL;
    char *arg = NULL;
    size_t size_arg = 0;
    char *str = NULL;
    while ((size_line = getline(&buffer, &size_buffer, stream)) != -1
           && buffer[0] != '\n')
    {
        save = strtok_r(buffer, "=", &save_buffer);
        size_arg = size_line - strlen(save) - 3;
        arg = strtok_r(NULL, "=", &save_buffer);
        str = malloc(sizeof(char) * size_arg + 1);
        for (size_t i = 0; i < size_arg; i++)
        {
            str[i] = arg[i + 1];
        }
        str[size_arg] = '\0';
        if (strcmp(save, "pid_file ") == 0)
        {
            config->pid_file = str;
        }
        else if (strcmp(save, "log_file ") == 0)
        {
            config->log_file = str;
        }
        else if (strcmp(save, "log ") == 0)
        {
            if (strcmp(str, "false") == 0)
            {
                config->log = 0;
            }
            free(str);
        }
    }
    free(buffer);
    return config;
}

static struct server_config server_creator(void)
{
    struct server_config server;
    ;
    server.server_name = NULL;
    server.port = NULL;
    server.ip = NULL;
    server.root_dir = NULL;
    server.default_file = NULL;
    return server;
}

static struct server_config assign_server(struct server_config server,
                                          FILE *stream)
{
    char *buffer = NULL;
    size_t size_buffer = 0;
    ssize_t size_line = 0;
    char *save_buffer = NULL;
    char *save = NULL;
    char *arg = NULL;
    size_t size_arg = 0;
    char *str = NULL;
    while ((size_line = getline(&buffer, &size_buffer, stream)) != -1
           && buffer[0] != '\n')
    {
        save = strtok_r(buffer, "=", &save_buffer);
        size_arg = size_line - strlen(save) - 3;
        arg = strtok_r(NULL, "=", &save_buffer);
        str = malloc(sizeof(char) * size_arg + 1);
        for (size_t i = 0; i < size_arg; i++)
        {
            str[i] = arg[i + 1];
        }
        str[size_arg] = '\0';
        if (strcmp(save, "server_name ") == 0)
        {
            server.server_name = string_create(str, size_arg);
            free(str);
        }
        else if (strcmp(save, "port ") == 0)
        {
            server.port = str;
        }
        else if (strcmp(save, "ip ") == 0)
        {
            server.ip = str;
        }
        else if (strcmp(save, "root_dir ") == 0)
        {
            server.root_dir = str;
        }
        else if (strcmp(save, "default_file ") == 0)
        {
            server.default_file = str;
        }
    }
    free(buffer);
    return server;
}

static int check_server(struct server_config server)
{
    if (server.server_name == NULL || server.port == NULL || server.ip == NULL
        || server.root_dir == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

static int check_config(struct config *config)
{
    if (config->pid_file == NULL || config->nb_servers == 0)
    {
        return 1;
    }
    else
    {
        for (size_t i = 0; i < config->nb_servers; i++)
        {
            if (check_server(config->servers[i]))
            {
                return 1;
            }
        }
        return 0;
    }
}

void config_destroy(struct config *config)
{
    if (config != NULL)
    {
        if (config->nb_servers != 0)
        {
            for (size_t i = 0; i < config->nb_servers; i++)
            {
                if (config->servers[i].server_name != NULL)
                {
                    string_destroy(config->servers[i].server_name);
                }
                if (config->servers[i].ip != NULL)
                {
                    free(config->servers[i].ip);
                }
                if (config->servers[i].root_dir != NULL)
                {
                    free(config->servers[i].root_dir);
                }
                if (config->servers[i].default_file != NULL)
                {
                    free(config->servers[i].default_file);
                }
                if (config->servers[i].port != NULL)
                {
                    free(config->servers[i].port);
                }
            }
            free(config->servers);
        }
        if (config->pid_file != NULL)
        {
            free(config->pid_file);
        }
        if (config->log_file != NULL)
        {
            free(config->log_file);
        }
        free(config);
    }
}

struct config *parse_configuration(const char *path)
{
    FILE *stream = fopen(path, "r");
    if (stream == NULL)
    {
        return NULL;
    }
    char *buffer = NULL;
    size_t size_buffer = 0;
    ssize_t size_line = 0;
    struct config *config = NULL;
    while ((size_line = getline(&buffer, &size_buffer, stream)) != -1)
    {
        if (buffer[0] == '[')
        {
            if (buffer[1] == '[')
            {
                config->servers = realloc(config->servers,
                                          sizeof(struct server_config)
                                              * (config->nb_servers + 1));
                config->servers[config->nb_servers++] =
                    assign_server(server_creator(), stream);
            }
            else
            {
                config = assign_config(config_creator(), stream);
            }
        }
    }
    fclose(stream);
    free(buffer);
    if (check_config(config))
    {
        config_destroy(config);
        return NULL;
    }
    return config;
}
