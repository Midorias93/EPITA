#define _POSIX_C_SOURCE 200809L

#include "httpd.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
    char message[] = "get SD test-les-amis SD TCP CRLF";
    struct request_line *ff = parse_request_line(message, creat_request_line());
    printf("%d\n", ff->methode);
    printf("%d\n", ff->protocol);
    printf("%s\n", ff->request);
    request_destroy(ff);
}
