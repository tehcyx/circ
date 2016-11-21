#include <server.h>
#include <client.h>
#include <pthread.h>
#include <string.h>
#include <regex.h>

#include <commands.h>
#include <stringutil.h>

const int BUFFER_SIZE = 512;

void client_connect(client_info* new_client) {
	char buf[BUFFER_SIZE], errMsg[BUFFER_SIZE];
	char* next = NULL;
	char* nick = NULL;
	char* recipient = NULL;

	pthread_t client_thread = new_client->thread;
	int client_sock = new_client->sock;

	bool quit = false;
	bool err = false;
	bool pass = false;

	for(;;) { // this is faster than while(true)
		quit = false;
		pass = true; // check if password is required, if yes, don't set to true here

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
			break;
		} else if (next == NULL) {
			continue;
		} else {
			printf("Received message from client: '%s'\n", next);
			trim_str(next);

			char* cmd = strtok(next, " ");
			char* args = strtok(NULL, " ");

			if (cmd == NULL) {
				printf("Empty msg received from client. Ignoring\n");
				continue;
			} else if (strcmp(cmd, PASS_CMD) == 0 && !pass) {
				client_read_connect_pass(cmd, args, &pass);
				continue;
			} else if (strcmp(cmd, NICK_CMD) == 0 && args != NULL && pass) {
				nick = client_read_connect_cmd(cmd, args);

				if (nick == NULL) {
					printf("NULL nick received from client\n");
					sprintf(errMsg, "%s :No nickname given", NICK_NULL);
					write(client_sock, errMsg, strlen(errMsg) + 1);
				} else if (client_nick_exists(nick)) {
					printf("Nick %s already exists.\n", nick);
					sprintf(errMsg, "%s * %s :Nickname is already in use\n", NICK_IN_USE, nick);
					write(client_sock, errMsg, strlen(errMsg) + 1);
					free(nick);
				} else if (!valid_charset(nick)) {
					printf("Nick %s not in valid charset.\n", nick);
					sprintf(errMsg, "%s * %s :Erroneous nickname\n ", NICK_INVALID, nick);
					write(client_sock, errMsg, strlen(errMsg) + 1);
					free(nick);
				} else {
					printf("Starting user init for '%s'.\n", nick);
					free(next);
					client_init(nick, client_sock, client_thread);
				}
				cmd = strtok(NULL, " ");
				if (cmd != NULL) {
					args = strtok(NULL, " ");
					if(strcmp(cmd, USER_CMD) == 0 && args != NULL) {

					}
				}
			} else if ((strcmp(cmd, PRIVMSG_CMD) == 0 && args != NULL) || (strcmp(cmd, NOTICE_CMD) == 0 && args != NULL)) {
				recipient = client_read_recipient(cmd, args);
				printf("Recipient is: %s\n", recipient);
				free(recipient);
			}
		}

		if (quit == true) {
			printf("Received %s command from client. Terminating client socket %d.\n", QUIT_CMD, client_sock);
			close(client_sock); //close socket
			free(next);
			pthread_exit(NULL); //free user
		}
	}
}

char* client_util_read_args(char* cmd, char* args) {
	char* argReturn;
	if (strstr(args, "\n") != 0) {
		char* arg1 = strtok(args, "\n");
		arg1[strlen(arg1)-1] = '\0';
		argReturn = (char*)malloc(sizeof(char)*(strlen(arg1) + 1));
		strcpy(argReturn, arg1);
	} else {
		argReturn = (char*)malloc(sizeof(char)*(strlen(args) + 1));
		strcpy(argReturn, args);
	}
	return argReturn;
}

char* client_read_recipient(char* cmd, char* args) {
	return client_util_read_args(cmd, args);
}

char* client_read_connect_cmd(char* cmd, char* args) {
	return client_util_read_args(cmd, args);
}

char* client_read_connect_pass(char* cmd, char* args, bool* quit) {
	// hello

	// 461 %s %s :Not enough parameters

	// 464 :Password incorrect
	return NULL;
}

char* client_read_socket(int socket, char* buffer, bool* err) {
	unsigned long bytes_read = -1;
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

void client_list_init() {//Create empty list of users if it hasn't been initialized
	client_list = list_create((void(*)(void*))client_free);
}

void client_free(client* c) {
	close(c->client_sock);
	pthread_mutex_destroy(&(c->client_sock_mutex));
	free(c->nick);
	free(c);
}

void client_init(char* nick, int client_sock, pthread_t client_thread) {
	client* new_client = (client*)malloc(sizeof(client));
	new_client->client_sock = client_sock;
	new_client->current_channel = NULL;
	new_client->nick = nick;
	new_client->client_thread = client_thread;
	pthread_mutex_init(&(new_client->client_sock_mutex), NULL);

	// pthread_mutex_lock(&users_mutex); //Atomically add user to list
	// add_to_list(client_list, new_client);
	// pthread_mutex_unlock(&users_mutex);

	// add_user_to_lobby(new_client);
}

bool client_nick_exists(char* nick) {
	client* tmp_u;
	bool exists = false;
	node* iter = client_list->head;

	while (iter != NULL) {
		tmp_u = (client*)iter->data;
		if (strcasecmp(tmp_u->nick, nick)==0) {
			exists = true;
			break;
		}
		iter=iter->next;
	}
	return exists;
}
