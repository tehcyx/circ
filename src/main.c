#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#include <sqlitedb.h>
#include <linkedlist.h>
#include <logger.h>
#include <server.h>
#include <client.h>
#include <channel.h>
#include <utils.h>

/* Define port to use */
#ifndef CIRC_PORT
#define CIRC_PORT "6665"
#endif

#ifndef CIRC_VERSION_MAJOR
#define CIRC_VERSION_MAJOR 0
#endif

#ifndef CIRC_VERSION_MINOR
#define CIRC_VERSION_MINOR 1
#endif

int main(int argc, char **argv) {
	db_init();

	log_init(NULL, LOG_DEBUG);

	mutexes_init();

	int socket_fd = server_run(CIRC_PORT);
	//log_info("Started server v%s.%s on port %s", CIRC_VERSION_MAJOR, CIRC_VERSION_MINOR, CIRC_PORT);

	int errno;

	client_list_init();

	channel_init();

	if ( (errno = server_sock_listen(socket_fd)) < 0) {
		fprintf(stderr, "Server could not start, listen on socket failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	server_accept(socket_fd);

	return 0;             /* ANSI C requires main to return int. */
}
