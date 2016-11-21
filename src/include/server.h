#ifndef _SERVER_H_
#define _SERVER_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "sys/socket.h"
#include "sys/types.h"
#include "netdb.h"
#include "errno.h"

typedef struct client_info_struct {
	pthread_t thread; 
	int sock; 
} client_info; 

int server_run(char* port);

int server_sock_listen(int sock_fd);

void server_accept(int sock_fd);

#endif
