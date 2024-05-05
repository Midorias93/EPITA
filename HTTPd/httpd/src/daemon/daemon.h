#ifndef DAEMON_H
#define DAEMON_H

#include "../config/config.h"

void start_deamon(int socket_server, struct config *config);

int get_pid(char *path_pid_file);
void sauv_pid(char *path_pid_file, int pid);
int is_deamon_a_life(int pid);

void start(int is_a_life, struct config *config,int server_socket);
void stop(int pid, int is_a_life, struct config *config);

char *my_itoa(int value, char *s);

#endif  // DAEMON_H
