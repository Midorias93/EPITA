#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>

#include "config.h"

int main(void)
{
    struct config *config = parse_configuration("./conf_test.conf");
    printf("log : %d\n", config->log);
    printf("log_file : %s\n", config->log_file);
    config_destroy(config);
}
