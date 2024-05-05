#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/epoll.h>
#include <unistd.h>

#define MAX_EVENT 10
#define BUFFER_SIZE 256

static void affiche(char *buffer, int *running, int size_read)
{
    buffer[size_read] = '\0';
    if (strcmp(buffer, "quit") == 0)
    {
        printf("quit\n");
        *running = 1;
    }
    else if (strcmp(buffer, "ping") == 0)
    {
        printf("pong!\n");
    }
    else if (strcmp(buffer, "pong") == 0)
    {
        printf("ping!\n");
    }
    else
    {
        printf("Unknown: %s\n", buffer);
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "./epoll: Bad usage ./epoll <pipe_name>\n");
        return 1;
    }

    struct epoll_event ev;
    struct epoll_event events[MAX_EVENT];
    int fd_listen = open(argv[1], O_RDWR);
    int epfd = epoll_create1(0);

    if (epfd == -1)
    {
        fprintf(stderr, "epoll_create1 (failed)\n");
        return 1;
    }

    ev.events = EPOLLIN;
    ev.data.fd = fd_listen;
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, fd_listen, &ev) == -1)
    {
        fprintf(stderr, "epoll_ctl (failed)\n");
        return 1;
    }

    int running = 0;

    while (1)
    {
        int nfds = epoll_wait(epfd, events, MAX_EVENT, -1);
        if (nfds == -1)
        {
            fprintf(stderr, "eppoll_wait (failed)\n");
            return 1;
        }

        for (int n = 0; n < nfds; n++)
        {
            if (events[n].data.fd == fd_listen)
            {
                char buffer[BUFFER_SIZE];
                ssize_t size_read =
                    read(events[n].data.fd, buffer, BUFFER_SIZE);
                if (size_read == -1)
                {
                    fprintf(stderr, "read failed\n");
                    return 1;
                }
                affiche(buffer, &running, size_read);
            }
        }
        if (running)
        {
            epoll_ctl(epfd, EPOLL_CTL_DEL, fd_listen, &ev);
            close(fd_listen);
            close(epfd);
            return 0;
        }
    }
}
