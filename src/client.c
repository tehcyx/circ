#include <server.h>
#include <client.h>
#include <pthread.h>
#include <string.h>
#include <regex.h>

#include <commands.h>
#include <utils.h>
#include <stringutil.h>
#include <channel.h>
#include <logger.h>

const uint16_t BUFFER_SIZE = 512;

void client_connect(client_info* cli) {
	char buf[BUFFER_SIZE], errMsg[BUFFER_SIZE];
	char* next = NULL;
	char* nick = NULL;

	pthread_t client_thread = cli->thread;
	int client_sock = cli->sock;

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
			log_error("An error occured, now closing connection to client socket. Error: %s\n", strerror(errno));
			close(client_sock);
			free(cli);
			if (next) {
				free(next);
			}
			pthread_exit(NULL);
			break;
		} else if (next == NULL) {
			continue; // nothing received yet, go on
		} else {
			trim_str(next);
			log_debug("Received message from client: '%s'\n", next);

			char* cmd = strtok(next, " ");
			char* args = strtok(NULL, " ");

			log_debug("COMMAND: %s, ARGS: %s\n", cmd, args);

			if (cmd == NULL) {
				log_debug("Empty msg received from client. Ignoring\n");
				continue;
			} else if (strcmp(cmd, PASS_CMD) == 0 && !pass) {
				client_read_connect_pass(cmd, args, &pass);
				continue;
			} else if (strcmp(cmd, NICK_CMD) == 0 && args != NULL && pass) {;
				nick = client_read_connect_cmd(cmd, args);

				if (nick == NULL) {
					log_debug("NULL nick received from client\n");
					sprintf(errMsg, "%s :No nickname given", NICK_NULL);
					write(client_sock, errMsg, strlen(errMsg) + 1);
				} else if (client_nick_exists(nick)) {
					log_debug("Nick %s already exists.\n", nick);
					sprintf(errMsg, "%s * %s :Nickname is already in use\n", NICK_IN_USE, nick);
					write(client_sock, errMsg, strlen(errMsg) + 1);
					free(nick);
				} else if (!valid_charset(nick)) {
					log_debug("Nick %s not in valid charset.\n", nick);
					sprintf(errMsg, "%s * %s :Erroneous nickname\n ", NICK_INVALID, nick);
					write(client_sock, errMsg, strlen(errMsg) + 1);
					free(nick);
				} else {
					log_debug("Starting NICK init for '%s'.\n", nick);
					free(next);
					client_init(nick, client_sock, client_thread);
				}
			}
		}

		if (quit == true) {
			log_debug("Received %s command from client. Terminating client socket %d.\n", REG_QUIT_CMD, client_sock);
			close(client_sock);
			free(cli);
			free(next);
			pthread_exit(NULL); //free user
			break;
		}
	}
}

char* client_read_connect_cmd(char* cmd, char* args) {
	char* nick;
	if(strstr(args, "\n") != 0) {
		char* arg1 = strtok(args, "\n");
		arg1[strlen(arg1)-1] = '\0';
		nick = (char*)malloc(sizeof(char)*(strlen(arg1) + 1));
		strcpy(nick, arg1);
	} else {
		nick = (char*)malloc(sizeof(char)*(strlen(args) + 1));
		strcpy(nick, args);
	}
	return nick;
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

	// if ((bytes_read = recv(socket, buf, BUFFER_SIZE, 0)) <= 0) {
	// 	*err = true;
	// 	return NULL;
	// }

	bytes_read = recv(socket, buf, BUFFER_SIZE - 1, 0);
	buf[bytes_read] = '\0';

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
	client* cli = (client*)malloc(sizeof(client));
	cli->client_sock = client_sock;
	cli->nick = nick;
	cli->client_thread = client_thread;
	pthread_mutex_init(&(cli->client_sock_mutex), NULL);

	node* n = create_node(cli);
	pthread_mutex_lock(&users_mutex); //to disable two thread working on the user list
	list_add(client_list, n);
	pthread_mutex_unlock(&users_mutex);

	log_debug("Adding user %s to LOBBY", cli->nick);
	channel_client_join(LOBBY, cli);
}

// bool client_nick_change(char* new_nick, char* old_nick, int client_sock, pthread_t client_thread) {
// 	client* tmp_u;
// 	bool exists = false;
// 	node* iter = client_list->head;

// 	while (iter != NULL) {
// 		tmp_u = (client*)iter->data;
// 		if(strcasecmp(tmp_u->nick, old_nick) == 0 && tmp_u->client_sock == client_sock && tmp_u->client_thread == client_thread) {
// 			tmp_u->nick = new_nick;
// 			exists = true;
// 			break;
// 		}
// 		iter=iter->next;
// 	}
// 	return exists;
// }

void client_set_prompt(client* cli, char* prompt) {
	char client_msg[BUFFER_SIZE]; 
	int bytes_written;
	
	sprintf(client_msg, "%s %s", PROMPT_CMD, prompt); 

	pthread_mutex_lock(&(cli->client_sock_mutex)); // atomic action
	bytes_written = send(cli->client_sock, client_msg, strlen(client_msg) + 1, 0);
	pthread_mutex_unlock(&(cli->client_sock_mutex)); 

	if (bytes_written < 0) {
		log_error("Error sending prompt.\nError: %s\n", strerror(errno)); 
	}
	else if (bytes_written == 0) {
		log_error("Error sending prompt: 0 bytes written.\nError: %s\n", strerror(errno)); 
	}
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
