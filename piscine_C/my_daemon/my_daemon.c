#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int signum)
{
    static int compteur = 0;
    static int current = 0;
    int pid = 0;
    switch (signum)
    {
    case SIGUSR1:
        compteur++;
        printf("Received %d signals.\n", compteur);
        fflush(NULL);
        break;
    case SIGUSR2:
        printf("Current generation: %d\n", current);
        fflush(NULL);
        compteur++;
        break;
    case SIGTERM:
        compteur = 0;
        current++;
        pid = fork();
        if (pid != 0)
        {
            exit(0);
        }
        break;
    case SIGINT:
        exit(0);
        break;
    default:
        break;
    }
}

int main(void)
{
    int pid = fork();
    if (pid != 0)
    {
        exit(0);
    }
    else
    {
        struct sigaction sa;
        sa.sa_flags = 0;
        sa.sa_handler = handler;
        if (sigemptyset(&sa.sa_mask) < 0)
        {
            return -1;
        }
        if (sigaction(SIGUSR1, &sa, NULL) < 0)
        {
            return -1;
        }
        if (sigaction(SIGUSR2, &sa, NULL) < 0)
        {
            return -1;
        }
        if (sigaction(SIGTERM, &sa, NULL) < 0)
        {
            return -1;
        }
        if (sigaction(SIGINT, &sa, NULL) < 0)
        {
            return -1;
        }
        while (1)
            ;
    }
}
