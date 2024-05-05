#define _POSIX_C_SOURCE 200809L

#include "httpd.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define SIZE_BUFFER 1024
#define SIZE_MESSAGE 256

struct request_line *creat_request_line(void)
{
    struct request_line *request_line = malloc(sizeof(struct request_line));
    request_line->methode = 0;
    request_line->request = NULL;
    request_line->protocol = 0;
    request_line->next = NULL;
    return request_line;
}

static char *str_alloc(char *str)
{
    size_t size_str = strlen(str);
    char *copy = malloc(sizeof(char) * (size_str + 1));
    for (size_t i = 0; i < size_str; i++)
    {
        copy[i] = str[i];
    }
    copy[size_str] = '\0';
    return copy;
}

static int whats_method(char *method)
{
    if (strcmp(method, "get") == 0)
    {
        return GET;
    }
    else if(strcmp(method, "head") == 0)
    {
        return HEAD;
    }
    else
    {
        return 0;
    }
}

static int whats_protocol(char *protocol)
{
    if(strcmp(protocol, "TCP") == 0)
    {
        return TCP;
    }
    else if(strcmp(protocol, "UDP") == 0)
    {
        return UDP;
    }
    else
    {
        return 0;
    }
}

struct request_line *parse_request_line(char *message, struct request_line request_line)
{
    struct request_line *n_r = creat_reques_line();
    char *save_ptr = NULL;
    char *str = strtok_r(message, " SD", &save_ptr);
    n_r->methode = whats_method(str);
    n_r->request = str_alloc(strtok_r(NULL," SD", &save_ptr));
    str = strtok_r(NULL, " SD", &save_ptr);
    n_r->protocol = whats_protocol(str);
    if (request_line != NULL)
    {
        request->next = n_r;
        return request->next;
    }
    else
    {
        return n_r;
    }
}

struct parse_entre(int sokcet_client)
{
    char *buffer[SIZE_BUFFER];
    char *message[SIZE_MESSAGE];
    char *saveptr = NULL;
    int indice = 0;

    ssize_t size_read = read(socket_client, buffer, SIZE_BUFFER);
    message = strtockt_r(buffer, " CRLF", &saveptr);
    



void request_destroy(struct request_line *r)
{
    free(r->request);
    free(r);
}
