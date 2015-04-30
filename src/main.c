#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#include <sqlitedb.h>
#include <linkedlist.h>
#include <logger.h>
#include <server.h>

/* Define port to use */
#ifndef CIRC_PORT
#define CIRC_PORT "6665"
#endif

#ifndef CIRC_VERSION
#define CIRC_VERSION 0.1
#endif

int main(int argc, char **argv) {

	init_db();

	int socket_fd = server_run(CIRC_PORT);

	int errno;

	if ( (errno = server_sock_listen(socket_fd)) < 0) {
		fprintf(stderr, "Server could not start, listen on socket failed: %s\n", strerror(errno)); 
		exit(EXIT_FAILURE); 
	}

	return 0;             /* ANSI C requires main to return int. */
}