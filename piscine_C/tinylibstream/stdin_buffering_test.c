#define _GNU_SOURCE
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct slow_cookie
{
    int fd;
};

static ssize_t slow_read(void *vcookie, char *buf, size_t count)
{
    struct slow_cookie *cookie = vcookie;
    usleep(500000); // sleep for half of a second

    ssize_t res;

    while ((res = read(cookie->fd, buf, count)) < 0)
        if (errno != EINTR && errno != EAGAIN)
            break;

    return res;
}

static int slow_close(void *vcookie)
{
    struct slow_cookie *cookie = vcookie;
    return close(cookie->fd);
}

cookie_io_functions_t slow_stdio = {
    .read = slow_read,
    .close = slow_close,
};

int main(void)
{
    /* setup a custom stdin stream with a slow read function */
    struct slow_cookie cookie = {
        .fd = STDIN_FILENO,
    };

    FILE *input_stream = fopencookie(&cookie, "r", slow_stdio);

    /* change the buffer size to the one given by stdbuf.
    ** it doesn't work out of the box as stdbuf only does
    ** this for the already existing stdin stream.
    */
    char *buffer = NULL;
    char *buffer_size = getenv("_STDBUF_I");
    if (buffer_size)
    {
        size_t size = atoi(buffer_size);
        buffer = malloc(size);
        setvbuf(input_stream, buffer, _IOFBF, size);
    }

    /* forward all characters from stdin to stdout */
    int c;
    while ((c = fgetc(input_stream)) != EOF)
    {
        fputc(c, stdout);
        fflush(stdout);
    }

    fclose(input_stream);
    free(buffer);
    return 0;
}
