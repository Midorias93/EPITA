#ifndef HTTPD_H
#define HTTPD_H

enum methodes
{
    GET = 1,
    HEAD,
};

enum ptrotocol
{
    TCP = 1,
    UDP,
};

struct request_line
{
    int methode;
    char *request;
    int protocol;
    struct request_line *next;
};

 
struct request_line *creat_request_line(void);
struct request_line *parse_request_line(char *message, struct request_line *resquest_line);
void request_destroy(struct request_line *r);

#endif // HTTPD_H
