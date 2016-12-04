#include <server.h>
#include <client.h>
#include <pthread.h>

static const uint16_t MAX_PENDING_CONNECTIONS = 1024;

int server_run(char* port) {
	struct addrinfo hints;
	struct addrinfo* addr;
	int socket_fd, errno;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	hints.ai_protocol = 0;
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;

	errno = getaddrinfo(NULL, port, &hints, &addr);									// get address to bind

	if (errno != 0) {
		fprintf(stderr, "Error calling getaddrinfo: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	struct addrinfo* iter;

	for (iter = addr; iter != NULL; iter = iter->ai_next) {							// try all sockets
		socket_fd = socket(iter->ai_family, iter->ai_socktype, iter->ai_protocol);

		if (socket_fd < 0)															// this one failed, try next
			continue;

		if (bind(socket_fd, iter->ai_addr, iter->ai_addrlen) == 0)					// success, use it
			break;

		fprintf(stderr, "Error calling bind: %s\n", strerror(errno));

		close(socket_fd);															// socket failed to bind, so this should be closed
	}

	freeaddrinfo(addr);																// free memory

	if (iter == NULL) {
		fprintf(stderr, "Error: Failed to bind a socket!\n");
		exit(EXIT_FAILURE);
	}

	printf("Started server on port %s.\n", port);

	return socket_fd;
}

int server_sock_listen(int sock_fd) {
	printf("Listening...\n");
	return listen(sock_fd, MAX_PENDING_CONNECTIONS);
}

void server_accept(int sock_fd) {
	int client_sock = -1;
	socklen_t client_length = sizeof(struct sockaddr);
	struct sockaddr client_addr;
	client_info* new_client;

	memset(&client_addr, 0, sizeof(struct sockaddr));

	for(;;) {
		client_sock = accept(sock_fd, &client_addr, &client_length);

		if (client_sock < 0) {
			printf("Client connection failed: %s\n", strerror(errno));
			continue;
		}

		new_client = (client_info*)malloc(sizeof(client_info));
		new_client->sock = client_sock;
		printf("Connecting client on socket %i\n", client_sock);
		pthread_create(&(new_client->thread), NULL, (void*(*)(void*))client_connect, (void*)(new_client));
	}
}
