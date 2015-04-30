#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "sys/socket.h"
#include "sys/types.h"
#include "netdb.h"
#include "errno.h"


int server_run(char* port);

int server_sock_listen(int sock_fd);