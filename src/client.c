#include <server.h>
#include <client.h>
#include <pthread.h>
#include <string.h>

const int BUFFER_SIZE = 512;

void client_connect(client_info* new_client) {
	char buf[BUFFER_SIZE];
	char* next = NULL;
	char* nick = NULL;

	pthread_t client_thread = new_client->thread;
	int client_sock = new_client->sock;

	bool quit = false;
	bool err = false;

	for(;;) { // this is faster than while(true)
		quit = false;

		if(next) {
			free(next);
		}

		next = client_read_socket(client_sock, buf, &err);

		if (err) {
			printf("An error occured, closing connection to client socket. Error: %s\n", strerror(errno));
			close(client_sock);
			free(new_client);
			if (next) {
				free(next);
			}
			pthread_exit(NULL);
		} else if (next == NULL) {
			continue;
		} else {
			printf("Received message from client: '%s'\n", next);
		}
	}
}

char* client_read_socket(int socket, char* buffer, bool* err) {
	int bytes_read = -1;
	char buf[BUFFER_SIZE];
	char* next;
	*err = false;

	if ((bytes_read = recv(socket, buf, BUFFER_SIZE, 0)) <= 0) {
		*err = true;
		return NULL;
	}

	size_t len = strnlen(buf, BUFFER_SIZE);

	if (len == BUFFER_SIZE) { // assuming there's no \0 in the string, so we're not done reading
		strncat(buffer, buf, bytes_read); //concatenate buffer onto current partial command 
		return NULL; //NULL means no new command
	} else { // \0 found, so finish command.
		strncat(buffer, buf, len);
		next = (char*)malloc(sizeof(char)*(BUFFER_SIZE));
		strcpy(next, buffer);
		buffer[0] = '\0';

		//If we received 2 commands simultaneously
		if (len + 1 < bytes_read) {
			strncpy(buffer, buf + (len + 1), bytes_read - (len + 1)); 
		}
		return next;
	}
}